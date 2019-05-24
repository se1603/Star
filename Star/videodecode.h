#ifndef VIDEODECODE_H
#define VIDEODECODE_H

#include <QThread>
#include <QImage>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
#include "libavutil/pixfmt.h"
#include "libswresample/swresample.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_audio.h"
#include "SDL2/SDL_types.h"
#include "SDL2/SDL_name.h"
#include "SDL2/SDL_main.h"
#include "SDL2/SDL_config.h"
#include "SDL2/SDL_mutex.h"
}

#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio
#define SDL_AUDIO_BUFFER_SIZE 1024  // 自定义SDL缓冲区大小

//存放音频包队列
typedef struct PacketQueue{
    AVPacketList *first_pkt,*last_pkt;
    int packets_count;
    int size;
    SDL_mutex *mutex;    //音频解码线程锁
    SDL_cond *cond;
} PacketQueue;

class VideoDecode;
class VideoPlayer;

typedef struct VideoState{
    //一帧
    AVFormatContext *formatCtx;

    int video_stream, audio_stream;

    //视频
    AVCodecContext *videoCodecCtx;
    AVCodec *videoCodec;
    AVStream *videoStream; //视频流
    PacketQueue videoQueue;  //视频队列

    //音频
    unsigned int audioBufferSize;
    unsigned int audioBufferIndex;
    SDL_AudioDeviceID audioID;    //音频设备ID
    int audio_hw_buffer_size;

    AVCodecContext *audioCodecCtx;
    AVCodec *audioCodec;
    AVStream *audioStream; //音频流
    PacketQueue audioQueue;  //存储音频队列
    AVPacket audioPacket; //音频包
    AVFrame *audioFrame; //解码音频使用的缓存
    int audioPacketSize;  //音频包数
    uint8_t *audioPacketData;  //音频包解码的数据大小

    enum AVSampleFormat audioSourceFormat;
    enum AVSampleFormat audioTargetFormat;

    int audioSourceChannels;  //声道数
    int audioTargetChannels;
    int64_t audioSourceChannelLayout; //通道数
    int64_t audioTargetChannelLayout;

    int audioSourceSampleRate; //样本率
    int audioTargetSampleRate;

    uint8_t *audioBuffer; //音频缓冲
//    DECLARE_ALIGNED(16,uint8_t,audioBuffer) [AVCODEC_MAX_AUDIO_FRAME_SIZE * 4];
    DECLARE_ALIGNED(16,uint8_t,audioSourceBuffer) [AVCODEC_MAX_AUDIO_FRAME_SIZE * 4]; //解码音频缓冲区

    struct SwrContext *swrCtx; //用于解码后的音频格式转换

    double audioClock; //音频时间
    double videoClock;

    //播放控制
    bool pause;  //暂停标志
    bool quit;  //停止
    bool readFinished;  //视频文件读取完毕
    bool readThreadFinished;  //读取线程已结束
    bool videoThreadFinished;  //视频线程已结束

    //跳转相关
    int seek_req; //跳转标志
    int64_t seek_pos; //跳转的位置 微秒
    int seek_flag_audio; //音频线程跳转标志
    int seek_flag_video; //视频线程跳转标志
    double seek_time; //跳转时间

    VideoDecode *decoder;

} VideoState;

class VideoDecode : public QThread
{
    Q_OBJECT
public:
    VideoDecode(VideoPlayer *vp);

    bool startPlay(QString path);
    void displayVideo(QImage image);

    enum PlayerState
    {
        Playing,
        Pause,
        Stop
    };

    bool play();
    bool pause();
    bool stop(bool isWait = false);  //参数表示是否等待所有的线程执行完毕再返回

    int64_t getTotalTime(); //单位微秒
    double getCurrentTime(); //单位秒

    void seek(int64_t pos);  //拖动进度条

protected:
    void run();   //重载函数

signals:
    void getOneFrame(QImage);   //获取到一帧发送信号
//    void sig_totalTime(qint64 duration);   //获取到视频时长发送信号
    void sig_StateChanged(VideoDecode::PlayerState state);

private:
    VideoPlayer *mPlayer;
    QString mVideoName;
    VideoState mVideoState;

    PlayerState mPlayerState;   //播放状态
};

#endif // VIDEODECODE_H
