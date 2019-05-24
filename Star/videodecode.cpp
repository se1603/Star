#include "videodecode.h"
#include <iostream>
#include "videoplayer.h"

#define MAX_AUDIO_SIZE (25 * 16 * 1024)
#define MAX_VIDEO_SIZE (25 * 256 * 1024)

#define FLUSH_DATA "FLUSH"


//初始化包
void packet_queue_init(PacketQueue *q)
{
    memset(q, 0, sizeof(PacketQueue));
    q->mutex = SDL_CreateMutex();
    q->cond = SDL_CreateCond();
    q->size = 0;
    q->packets_count = 0;
    q->first_pkt = NULL;
    q->last_pkt = NULL;
}

//存储音频包到队列
int packet_queue_put(PacketQueue *q, AVPacket *pkt)
{
    AVPacketList *pkt1;

    //将共享内存里的AVPacket复制到独立的BUffer中
    if (av_dup_packet(pkt) < 0) {
        return -1;
    }
    //分配内存
    pkt1 = (AVPacketList*)av_malloc(sizeof(AVPacketList));
    if (!pkt1)
        return -1;

    pkt1->pkt = *pkt;
    pkt1->next = NULL;

    SDL_LockMutex(q->mutex); //线程加锁

    if (!q->last_pkt)
        q->first_pkt = pkt1;
    else
        q->last_pkt->next = pkt1;
    q->last_pkt = pkt1;
    q->packets_count++;
    q->size += pkt1->pkt.size;
    SDL_CondSignal(q->cond);

    SDL_UnlockMutex(q->mutex);  //解锁
    return 0;
}

//获取队列中的音频包
static int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block)
{
    AVPacketList *pkt1;
    int ret;

    SDL_LockMutex(q->mutex);

    for (;;) {

        pkt1 = q->first_pkt;
        if (pkt1) {
            q->first_pkt = pkt1->next;
            if (!q->first_pkt)
                q->last_pkt = NULL;
            q->packets_count--;
            q->size -= pkt1->pkt.size;
            *pkt = pkt1->pkt;
            av_free(pkt1);
            ret = 1;
            break;
        } else if (!block) {
            ret = 0;
            break;
        } else {
            SDL_CondWait(q->cond, q->mutex);
        }

    }

    SDL_UnlockMutex(q->mutex);
    return ret;
}

static void packet_queue_flush(PacketQueue *q)
{
    AVPacketList *pkt, *pkt1;

    SDL_LockMutex(q->mutex);
    for(pkt = q->first_pkt; pkt != NULL; pkt = pkt1)
    {
        pkt1 = pkt->next;

        if(pkt1->pkt.data != (uint8_t *)"FLUSH")
        {

        }
        av_free_packet(&pkt->pkt);
        av_freep(&pkt);

    }
    q->last_pkt = NULL;
    q->first_pkt = NULL;
    q->packets_count = 0;
    q->size = 0;
    SDL_UnlockMutex(q->mutex);
}

static int decodeAudio(VideoState *videostate,double *pts_ptr)
{
    AVPacket *packet = &videostate->audioPacket;

    int got_frame = 0;
    int decode_data_size = 0;
    int channel_layout = 0; //声道个数
    int nb_samples = 0; //样本率
    int resampled_data_size = 0; //重采样数据大小

    double pts = 0; //时间戳

    while (1) {

        while (videostate->audioPacketSize > 0)
        {
            if(videostate->pause == true)
            {
                SDL_Delay(10);
                continue;
            }

            if(!videostate->audioFrame)
            {
                //分配内存
                if(!(videostate->audioFrame = av_frame_alloc()))
                {
                    return AVERROR(ENOMEM);  //没有足够的内存
                }
            }
            else {
                av_frame_unref(videostate->audioFrame); //清空

                //                av_frame_free(&videostate->audioFrame);
            }

            int length = avcodec_decode_audio4(videostate->audioStream->codec,
                                               videostate->audioFrame,&got_frame,packet);
            if(length < 0)
            {
                //解码出错，跳过此帧
                videostate->audioPacketSize = 0;
                break;
            }

            videostate->audioPacketData += length;
            videostate->audioPacketSize -= length;

            if(!got_frame)  //未获取到帧跳过
                continue;

            //计算解码出来的帧需要的缓冲大小
            decode_data_size = av_samples_get_buffer_size(nullptr,
                                                          videostate->audioFrame->channels,
                                                          videostate->audioFrame->nb_samples,
                                                          (AVSampleFormat)videostate->audioFrame->format,1);

            //输出声道个数
            channel_layout = (videostate->audioFrame->channel_layout &&
                              videostate->audioFrame->channels == av_get_channel_layout_nb_channels(
                                  videostate->audioFrame->channel_layout)) ?
                        videostate->audioFrame->channel_layout : av_get_default_channel_layout(
                            videostate->audioFrame->channels);

            //样本大小
            nb_samples = videostate->audioFrame->nb_samples;

            //音频重采样设置
            if(videostate->audioFrame->format != videostate->audioSourceFormat
                    || channel_layout != videostate->audioSourceChannelLayout
                    || videostate->audioFrame->sample_rate != videostate->audioSourceSampleRate
                    || (nb_samples != videostate->audioFrame->nb_samples
                        && !videostate->swrCtx))
            {
                if(videostate->swrCtx)
                    swr_free(&videostate->swrCtx);
                videostate->swrCtx = swr_alloc_set_opts(NULL,videostate->audioTargetChannelLayout,
                                                        (AVSampleFormat)videostate->audioTargetFormat,
                                                        videostate->audioTargetSampleRate,
                                                        channel_layout,(AVSampleFormat)videostate->audioFrame->format,
                                                        videostate->audioFrame->sample_rate,0,
                                                        NULL);

                if(!videostate->swrCtx || swr_init(videostate->swrCtx) < 0)
                {
                    std::cout << "音频重采样失败。" << std::endl;
                    break;
                }

                //通道数
                videostate->audioSourceChannelLayout = channel_layout;
                //声道
                videostate->audioSourceChannels = videostate->audioStream->codec->channels;
                //采样率
                videostate->audioSourceSampleRate = videostate->audioStream->codec->sample_rate;
                //采样格式
                videostate->audioSourceFormat = videostate->audioStream->codec->sample_fmt;
            }

            //调整采样数，同步音画
            if(videostate->swrCtx)
            {
                const uint8_t **in = (const uint8_t **)videostate->audioFrame->extended_data;
                uint8_t *out[] = {videostate->audioSourceBuffer};
                if(nb_samples != videostate->audioFrame->nb_samples)
                {
                    int sample_delta = (nb_samples - videostate->audioFrame->nb_samples) *
                            videostate->audioTargetSampleRate /
                            videostate->audioFrame->sample_rate;
                    int compensation_distance = nb_samples * videostate->audioTargetSampleRate
                            / videostate->audioFrame->sample_rate;

                    if(swr_set_compensation(videostate->swrCtx,sample_delta,compensation_distance)
                            < 0)
                        break;
                }

                /*avcodec_decode_audio4函数解码音频，
                 * 得到的数据类型为float 4bit，而播放器播放的格式一般为S16（signed 16bit)
                   需要调用该函数转换格式*/
                int datalen = sizeof (videostate->audioSourceBuffer)
                        / videostate->audioTargetChannels /
                        av_get_bytes_per_sample(videostate->audioTargetFormat);
                int data = swr_convert(videostate->swrCtx,out,datalen,in,
                                       videostate->audioFrame->nb_samples);
                if(data < 0){
                    std::cout << "转化音频数据失败。" << std::endl;
                }

                if(data == datalen)
                {
                    swr_init(videostate->swrCtx);
                }
                videostate->audioBuffer = videostate->audioSourceBuffer;
                resampled_data_size = data * videostate->audioTargetChannels *
                        av_get_bytes_per_sample(videostate->audioTargetFormat);
            }
            else {
                resampled_data_size = decode_data_size;
                videostate->audioBuffer = videostate->audioFrame->data[0];
            }

            pts = videostate->audioClock;
            *pts_ptr = pts;

            int channels = 2 * videostate->audioStream->codec->channels;
            videostate->audioClock += (double)resampled_data_size /
                    (double)(channels * videostate->audioStream->codec->sample_rate);

            if (videostate->seek_flag_audio)
            {
                //发生了跳转 则跳过关键帧到目的时间的这几帧
               if (videostate->audioClock < videostate->seek_time)
               {
                   break;
               }
               else
               {
                   videostate->seek_flag_audio = 0;
               }
            }

            return resampled_data_size;
        }

        //暂停
        if(videostate->pause == true)
        {
            SDL_Delay(10);
            continue;
        }

        if(packet->data)
            av_free_packet(packet);
        memset(packet,0,sizeof(*packet));

        if (videostate->quit)
            return -1;

        if(packet_queue_get(&videostate->audioQueue,packet,0) <= 0)
            return -1;

        //收到这个数据 说明刚刚执行过跳转 现在需要把解码器的数据 清除一下
        if(strcmp((char*)packet->data,FLUSH_DATA) == 0)
        {
            avcodec_flush_buffers(videostate->audioStream->codec);
            av_free_packet(packet);
            continue;
        }

        videostate->audioPacketData = packet->data;
        videostate->audioPacketSize = packet->size;

        //如果更新，刷新音频时钟
        if(packet->pts != AV_NOPTS_VALUE)
        {
            videostate->audioClock = av_q2d(videostate->audioStream->time_base) * packet->pts;
        }
    }
    return 0;
}

static void audio_callback(void *userdata,Uint8 *stream,int bufferSize)
{
    VideoState *videostate = (VideoState *) userdata;

    int audio_data_size = 0;

    double pts;
    int size;

    //bufferSize是由SDL传入的SDL缓冲区大小，若缓冲区没满，就往里面填数据
    while (bufferSize > 0) {
        /*  audioBufferIndex 和 audioBufferSize 标示我们自己用来放置解码出来的数据的缓冲区，
          这些数据待复制到SDL缓冲区， 当audioBufferIndex >= audioBufferSize的时候意味着我
          们的缓冲为空，没有数据可供复制，这时候需要调用audio_decode_frame来解码出更
          多的桢数据 */

        //音频解码
        if(videostate->audioBufferIndex >= videostate->audioBufferSize)
        {
            audio_data_size = decodeAudio(videostate,&pts);

            if(audio_data_size < 0)
            {
                videostate->audioBufferSize = 1024;
                //清零，静音
                if(videostate->audioBuffer == NULL) return;
                memset(videostate->audioBuffer,0,videostate->audioBufferSize);
            }
            else {
                videostate->audioBufferSize = audio_data_size;
            }
            videostate->audioBufferIndex = 0;
        }

        /*  查看stream可用空间，决定一次复制多少数据，剩下的下次继续复制 */
        size = videostate->audioBufferSize - videostate->audioBufferIndex;
        if(size > bufferSize){
            size = bufferSize;
        }

        if (videostate->audioBuffer == NULL) return;

        //将解码后的音频复制到SDL缓冲区
        memcpy(stream,(uint8_t*)videostate->audioBuffer + videostate->audioBufferIndex,size);

        bufferSize -= size;
        stream += size;
        videostate->audioBufferIndex += size;
    }
}

static double get_audio_clock(VideoState *videostate)
{
    double pts;
    int hw_buf_size, bytes_per_sec, n;

    pts = videostate->audioClock; /* maintained in the audio thread */
    hw_buf_size = videostate->audioBufferSize - videostate->audioBufferIndex;
    bytes_per_sec = 0;
    n = videostate->audioStream->codec->channels * 2;
    if(videostate->audioStream)
    {
        bytes_per_sec = videostate->audioStream->codec->sample_rate * n;
    }
    if(bytes_per_sec)
    {
        pts -= (double)hw_buf_size / bytes_per_sec;
    }
    return pts;
}

static double synchronize_video(VideoState *videostate, AVFrame *src_frame, double pts) {

    double frame_delay;

    if (pts != 0) {
        /* if we have pts, set video clock to it */
        videostate->videoClock = pts;
    } else {
        /* if we aren't given a pts, set it to the clock */
        pts = videostate->videoClock;
    }
    /* update the video clock */
    frame_delay = av_q2d(videostate->videoStream->codec->time_base);
    /* if we are repeating a frame, adjust clock accordingly */
    frame_delay += src_frame->repeat_pict * (frame_delay * 0.5);
    videostate->videoClock += frame_delay;
    return pts;
}

int openAudioStreamCompent(VideoState *videostate, int streamIndex)
{
    AVFormatContext *aFormatContext = videostate->formatCtx;
    AVCodecContext *aCodecContext;
    AVCodec *aCodec;

    SDL_AudioSpec need_spec,spec;
    int64_t need_channel_layout = 0;
    int need_nb_channnels;

    /*  SDL支持的声道数为 1, 2, 4, 6 */
    /*  后面会使用这个数组来纠正不支持的声道数目 */
    const int next_nb_channels[] = {0,0,1,6,2,6,4,6};

    if(streamIndex < 0 || streamIndex >= aFormatContext->nb_streams)
    {
        return -1;
    }

    //解码器
    aCodecContext = aFormatContext->streams[streamIndex]->codec;
    need_nb_channnels = aCodecContext->channels;
    if(!need_channel_layout || need_nb_channnels !=
            av_get_channel_layout_nb_channels(need_channel_layout))
    {
        need_channel_layout = av_get_default_channel_layout(need_nb_channnels);
        need_channel_layout &= ~AV_CH_LAYOUT_STEREO_DOWNMIX;
    }

    need_spec.channels = av_get_channel_layout_nb_channels(need_channel_layout);
    need_spec.freq = aCodecContext->sample_rate;
    if(need_spec.freq <= 0 || need_spec.channels <=0)
    {
        std::cout << "Invalid sample rate or channel count!" << std::endl;
        return -1;
    }

    need_spec.format = AUDIO_S16SYS;   //格式
    need_spec.silence = 0;   //静音
    need_spec.samples = SDL_AUDIO_BUFFER_SIZE; //SDL缓冲区大小
    need_spec.callback = audio_callback; //音频解码的回调函数
    need_spec.userdata = videostate;  //传回外带数据

    /*  打开音频设备，这里使用一个while来循环尝试打开不同的声道数
     * (由上面next_nb_channels数组指定）直到成功打开，或者全部失败 */
    do{
        videostate->audioID = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0,0),0,
                                                  &need_spec,&spec,0);
        need_spec.channels = next_nb_channels[FFMIN(7,need_spec.channels)];
        if(!need_spec.channels)
        {
            std::cout << "No more channel combinations to tyu, audio open failed." << std::endl;
            break;
        }
        need_channel_layout = av_get_default_channel_layout(need_spec.channels);
    }while(videostate->audioID == 0);

    /* 检查实际使用的配置（保存在spec,由SDL_OpenAudio()填充） */
    if(spec.format != AUDIO_S16SYS)
    {
        std::cout << "SDL advised audio format " <<
                     spec.format <<" is not supported!" << std::endl;
        return -1;
    }

    if(spec.channels != need_spec.channels)
    {
        need_channel_layout = av_get_default_channel_layout(spec.channels);
        if(!need_channel_layout)
        {
            std::cout << "SDL advised channel count "
                      << spec.channels << " is not supported!" << std::endl;
            return -1;
        }
    }

    videostate->audio_hw_buffer_size = spec.size;

    /* 把设置好的参数保存到大结构中 */
    videostate->audioSourceFormat = videostate->audioTargetFormat = AV_SAMPLE_FMT_S16;
    videostate->audioSourceSampleRate = videostate->audioTargetSampleRate = spec.freq;
    videostate->audioSourceChannelLayout = videostate->audioTargetChannelLayout = need_channel_layout;
    videostate->audioSourceChannels = videostate->audioTargetChannels = spec.channels;

    aCodec = avcodec_find_decoder(aCodecContext->codec_id);
    if(!aCodec || (avcodec_open2(aCodecContext,aCodec,nullptr) < 0))
    {
        std::cout << "Unsupported codec!\n";
        return -1;
    }
    aFormatContext->streams[streamIndex]->discard = AVDISCARD_DEFAULT;
    switch (aCodecContext->codec_type) {
    case AVMEDIA_TYPE_AUDIO:
        videostate->audioStream = aFormatContext->streams[streamIndex];
        videostate->audioBufferSize = 0;
        videostate->audioBufferIndex = 0;
        memset(&videostate->audioPacket,0,sizeof (videostate->audioPacket));
        packet_queue_init(&videostate->audioQueue);
        SDL_PauseAudioDevice(videostate->audioID,0);
        break;
    default:
        break;
    }
}

//解码视频
int decodeVideo(void *arg)
{
    VideoState *vs = (VideoState *) arg;
    AVPacket pkt1;
    AVPacket *packet = &pkt1;

    double video_pts = 0; //当前视频的pts(显示时间戳)
    double audio_pts = 0; //音频pts

    //解码视频相关
    AVFrame *pFrame, *pFrameRGB;
    uint8_t *out_buffer_rgb;  //解码后的rgb数据

    static struct SwsContext *img_convert_ctx;  //解码后的视频格式转换

    AVCodecContext *pCodecCtx = vs->videoStream->codec;  //视频解码器

    //分配内存
    pFrame = av_frame_alloc();
    pFrameRGB = av_frame_alloc();

    int ret, got_picture,numBytes;

    //将解码后的YUV数据转换成RGB32
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
                                     pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
                                     AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);

    numBytes = avpicture_get_size(AV_PIX_FMT_RGB32, pCodecCtx->width,pCodecCtx->height);

    out_buffer_rgb = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *) pFrameRGB, out_buffer_rgb, AV_PIX_FMT_RGB32,
                   pCodecCtx->width, pCodecCtx->height);

    while(1)
    {
        if(vs->quit)
        {
            break;
        }

        if(vs->pause == true)  //判断暂停
        {
            SDL_Delay(10);
            continue;
        }

        if (packet_queue_get(&vs->videoQueue, packet, 1) <= 0)
        {
            if(vs->readFinished)
                break;//队列里面没有数据了  读取完毕了
            else {
                SDL_Delay(1); //队列只是暂时没有数据而已
                continue;
            }
        }

        //收到这个数据 说明刚刚执行过跳转 现在需要把解码器的数据 清除一下
        if(strcmp((char*)packet->data,FLUSH_DATA) == 0)
        {
            avcodec_flush_buffers(vs->videoStream->codec);
            av_free_packet(packet);
            continue;
        }

        ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,packet);

        if (ret < 0) {
            std::cout <<"decode error.\n";
            av_free_packet(packet);
            continue;
        }

        if(packet->dts == AV_NOPTS_VALUE && pFrame->opaque&& *(uint64_t*) pFrame->opaque != AV_NOPTS_VALUE)
        {
            video_pts = *(uint64_t *) pFrame->opaque;
        }
        else if (packet->dts != AV_NOPTS_VALUE) {
            video_pts = packet->dts;
        }
        else {
            video_pts = 0;
        }

        video_pts *= av_q2d(vs->videoStream->time_base);
        video_pts = synchronize_video(vs, pFrame, video_pts);

        if (vs->seek_flag_video)
        {
            //发生了跳转 则跳过关键帧到目的时间的这几帧
           if (video_pts < vs->seek_time)
           {
               av_free_packet(packet);
               continue;
           }
           else
           {
               vs->seek_flag_video = 0;
           }
        }

        while(1)
        {
            if(vs->quit)
            {
                break;
            }
            audio_pts = vs->audioClock;

            //主要是 跳转的时候 我们把video_clock设置成0了
            //因此这里需要更新video_pts
            //否则当从后面跳转到前面的时候 会卡在这里
            video_pts = vs->videoClock;

            if (video_pts <= audio_pts) break;

            int delayTime = (video_pts - audio_pts) * 1000;

            delayTime = delayTime > 5 ? 5:delayTime;

            SDL_Delay(delayTime);
        }

        if (got_picture) {
            sws_scale(img_convert_ctx,
                      (uint8_t const * const *) pFrame->data,
                      pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                      pFrameRGB->linesize);
            QImage tmpImg((uchar *)out_buffer_rgb,pCodecCtx->width,pCodecCtx->height,QImage::Format_RGB32);
            QImage image = tmpImg.copy();
            vs->decoder->displayVideo(image);

        }
        av_free_packet(packet);
    }

    av_free(out_buffer_rgb);
    av_free(pFrameRGB);
    av_free(pFrame);

    if(!vs->quit)
    {
        vs->quit = true;
    }

    vs->videoThreadFinished = true;

    return 0;
}

VideoDecode::VideoDecode(VideoPlayer *vp)
{
    mPlayer = vp;
    mPlayerState = Stop;
    //    mVideoState.audioBuffer = NULL;
    //    bzero(mVideoState.audioSourceBuffer,sizeof (mVideoState.audioSourceBuffer));
    //    mVideoState.audioBufferIndex = 0;
    //    mVideoState.audioBufferSize = 0;
    //    mVideoState.audioFrame = 0;
    //    mVideoState.audioPacketSize = NULL;
    //    mVideoState.formatCtx = NULL;
    //    packet_queue_init(&mVideoState.audioQueue);
    //    packet_queue_init(&mVideoState.videoQueue);
    //    mVideoState.audioPacketData = NULL;
    //    mVideoState.audioStream = NULL;
    //    mVideoState.audioCodec = NULL;
    //    mVideoState.audioCodecCtx = NULL;
    //    mVideoState.audioID = 0;
    //    mVideoState.audioSourceChannels = 0;
    //    mVideoState.audioSourceChannelLayout = 0;
    //    mVideoState.audioSourceSampleRate = 0;
    //    mVideoState.audioTargetChannels = 0;
    //    mVideoState.audioTargetChannelLayout = 0;
    //    mVideoState.audioTargetSampleRate = 0;
    //    mVideoState.audio_hw_buffer_size = 0;
    //    mVideoState.videoCodec = NULL;
    //    mVideoState.videoCodecCtx = NULL;
    //    mVideoState.videoStream = NULL;
}

bool VideoDecode::startPlay(QString path)
{
    if(mPlayerState != Stop)
    {
        return false;
    }

    mVideoName = path;

    this->start();

    mPlayerState = Playing;

    return true;
}

void VideoDecode::displayVideo(QImage image)
{
    emit getOneFrame(image);
}

bool VideoDecode::play()
{
    mVideoState.pause = false;

    if(mPlayerState != Pause)
    {
        return false;
    }

    mPlayerState = Playing;

    return true;
}

bool VideoDecode::pause()
{
    mVideoState.pause = true;

    if(mPlayerState != Playing)
    {
        return true;
    }

    mPlayerState = Pause;

    return true;
}

bool VideoDecode::stop(bool isWait)
{
    if(mPlayerState == Stop)
    {
        return false;
    }

    mVideoState.quit = true;

    if(isWait)
    {
        while (!mVideoState.readThreadFinished || !mVideoState.videoThreadFinished) {
            SDL_Delay(10);
        }
    }

    //关闭SDL音频播放器
    if(mVideoState.audioID != 0)
    {
        SDL_LockAudio();
        SDL_PauseAudioDevice(mVideoState.audioID,1);
        SDL_UnlockAudio();

        mVideoState.audioID = 0;
    }

    mPlayerState = Stop;

    return true;
}

int64_t VideoDecode::getTotalTime()
{
    return mVideoState.formatCtx->duration;
}

double VideoDecode::getCurrentTime()
{
    return mVideoState.audioClock;
}

void VideoDecode::seek(int64_t pos)
{
    if(!mVideoState.seek_req)
    {
        mVideoState.seek_pos = pos;
        mVideoState.seek_req = true;
    }
}

void VideoDecode::run()
{
    char video[512] = {0};
    strcpy(video,mVideoName.toUtf8().data());

    memset(&mVideoState,0,sizeof (VideoState));

    VideoState *vs = &mVideoState;

    //一帧
    AVFormatContext *pFormatCtx;

    //视频
    AVCodecContext *pCodecCtx;
    AVCodec *pCodec;

    //音频
    AVCodecContext *aCodecCtx;
    AVCodec *aCodec;

    int audioStream = -1;
    int videoStream = -1;

    //分配存储空间
    pFormatCtx = avformat_alloc_context();

    //打开视频
    if (avformat_open_input(&pFormatCtx,video, NULL, NULL) != 0) {
        std::cout << "can't open the file. \n";
        return;
    }

    //获取视频信息
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        std::cout << "Could't find stream infomation.\n";
        return;
    }

    //循环查找视频中包含的流信息，
    for (int i = 0; i < pFormatCtx->nb_streams; i++) {
        //视频流
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = i;
        }
        //音频流
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO  && audioStream < 0)
        {
            audioStream = i;
        }
    }

    //如果为-1 说明没有找到流
    if (videoStream == -1) {
        std::cout << "Didn't find a video stream.\n";
        return;
    }

    if (audioStream == -1) {
        std::cout << "Didn't find a audio stream.\n";
        return;
    }
    mVideoState.formatCtx = pFormatCtx;
    mVideoState.video_stream = videoStream;
    mVideoState.audio_stream = audioStream;

    mPlayer->getTotalTime(getTotalTime());  //发送视频时长

    if (audioStream >= 0) {
        /* 所有设置SDL音频流信息的步骤都在这个函数里完成 */
        openAudioStreamCompent(&mVideoState, audioStream);
    }

    //查找音频解码器
    aCodecCtx = pFormatCtx->streams[audioStream]->codec;
    aCodec = avcodec_find_decoder(aCodecCtx->codec_id);

    if (aCodec == NULL) {
        std::cout << "ACodec not found.\n";
        return;
    }

    //打开音频解码器
    if (avcodec_open2(aCodecCtx, aCodec, NULL) < 0) {
        std::cout << "Could not open audio codec.\n";
        return;
    }

    mVideoState.audioStream = pFormatCtx->streams[audioStream];

    //查找视频解码器
    pCodecCtx = pFormatCtx->streams[videoStream]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

    if (pCodec == NULL) {
        std::cout << "PCodec not found.\n";
        return;
    }

    //打开视频解码器
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        std::cout << "Could not open video codec.\n";
        return;
    }

    mVideoState.videoStream = pFormatCtx->streams[videoStream];
    packet_queue_init(&mVideoState.videoQueue);

    //创建线程解码视频
    SDL_CreateThread(decodeVideo,"decodeVideo",&mVideoState);

    mVideoState.decoder = this;

    //    std::thread videoThread(decodeVideo,&mVideoState);
    //    videoThread.detach();

    //存放读取的视频
    AVPacket *packet = (AVPacket *)malloc(sizeof(AVPacket));

    //输出视频信息
    av_dump_format(pFormatCtx, 0, video, 0);

    while (1) {

        if(mVideoState.quit)  //停止播放了
        {
            break;
        }

        if(mVideoState.seek_req)
        {
            int streamIndex = -1;
            int64_t seek_target = mVideoState.seek_pos;

            if(mVideoState.video_stream >= 0)
            {
                streamIndex = mVideoState.video_stream;
            }
            else if (mVideoState.audio_stream >= 0) {
                streamIndex = mVideoState.audio_stream;
            }

            AVRational avRational = {1,AV_TIME_BASE};
            if(streamIndex >= 0)
            {
                seek_target = av_rescale_q(seek_target,avRational,
                                           pFormatCtx->streams[streamIndex]->time_base);
            }

            if(av_seek_frame(mVideoState.formatCtx,streamIndex,seek_target,AVSEEK_FLAG_BACKWARD) < 0){
                fprintf(stderr, "%s: error while seeking\n",mVideoState.formatCtx->filename);
            }
            else {
                if(mVideoState.audio_stream >= 0)
                {
                    AVPacket *packet = (AVPacket *)malloc(sizeof (AVPacket)); //分配一个packet
                    av_new_packet(packet,10);
                    strcpy((char *)packet->data,FLUSH_DATA);
                    packet_queue_flush(&mVideoState.audioQueue);  //清除队列
                    packet_queue_put(&mVideoState.audioQueue,packet);  //往队列中存入用来清除的包
                }
                if(mVideoState.video_stream >= 0)
                {
                    AVPacket *packet = (AVPacket *)malloc(sizeof (AVPacket)); //分配一个packet
                    av_new_packet(packet,10);
                    strcpy((char *)packet->data,FLUSH_DATA);
                    packet_queue_flush(&mVideoState.videoQueue);  //清除队列
                    packet_queue_put(&mVideoState.videoQueue,packet);  //往队列中存入用来清除的包
                }
            }
            mVideoState.seek_req = 0;
            mVideoState.seek_time = mVideoState.seek_pos / 1000000.0;
            mVideoState.seek_flag_audio = 1;
            mVideoState.seek_flag_video = 1;
        }

        //限制，当队列里的数据超过这个值时，暂停读取
        if (mVideoState.audioQueue.size > MAX_AUDIO_SIZE ||
                mVideoState.videoQueue.size > MAX_VIDEO_SIZE) {
            SDL_Delay(10);
            continue;
        }

        //暂停
        if(mVideoState.pause == true)
        {
            SDL_Delay(10);
            continue;
        }

        if(av_read_frame(pFormatCtx, packet) < 0)//视频已读完
        {
            mVideoState.readFinished = true;

            if(mVideoState.quit)  //解码线程已执行完，可以退出了
            {
                break;
            }
            SDL_Delay(10);
            continue;
        }

        if(packet->stream_index == videoStream)
        {
            packet_queue_put(&mVideoState.videoQueue,packet);
        }
        else if (packet->stream_index == audioStream) {
            packet_queue_put(&mVideoState.audioQueue, packet);
        }
        else {
            av_free_packet(packet);
        }
    }

    //文件读取结束，跳出循环。等待播放完毕
    while(!mVideoState.quit)
    {
        SDL_Delay(100);
    }

    stop();

    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);

    mVideoState.readThreadFinished = true;
}
