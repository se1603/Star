#include "datasource.h"
#include <string.h>
#include <sys/time.h>
#include  <unistd.h>

DataSource::DataSource()
{
    memset(m_sdp, 0, sizeof (m_sdp));
    m_range = 0;
    m_mediaNum = MAX_MEDIA_NUM;
    memset(m_media_info, 0, sizeof (m_media_info));
    m_start_sec = 0;
    m_end_sec = 0;
    m_sock = NULL;
    m_rtp_ch = 0;
    m_start_pcr = -1;
    m_start_ms = -1;
    m_last_pcr = -1;
    threadpool = new ThreadPool(1);
}

int DataSource::init(const char *fileName)
{
    if(m_reader.openFile(fileName) < 0)
        return -1;
    m_range = m_reader.getFileRange();
    m_end_sec = m_range;
    strncpy(m_media_info[0].track_id, "track1", sizeof (m_media_info[0].track_id));
    snprintf(m_sdp,sizeof (m_sdp),
             "v=0\r\n"
             "o=- 0 1 IN IP4 0.0.0.0\r\n"
             "s=RTSP Server\r\n"
             "i=%s\r\n"
             "t=0 0\r\n"
             "a=control:*\r\n"
             "a=range:npt=0-%d\r\n"
             "m=video 0 RTP/AVP 33\r\n"
             "a=control:%s\r\n",
             fileName,m_range,m_media_info[0].track_id);
    return 0;
}

const char *DataSource::getSdp()
{
    return m_sdp;
}

int DataSource::getRange()
{
    return m_range;
}

int DataSource::getMediaNum()
{
    return m_mediaNum;
}

void DataSource::rtpSendFrame()
{
    int ret = 0;
    while(1)
    {
        int sleep_ms = 5;
        if(m_sock != NULL)
        {
            char buf[TSPKTLEN * 7 + sizeof (RtpTcpHeader) + sizeof (RtpHeader)] = "";
            int len = 0;
            RtpTcpHeader* tcpHeader = NULL;
            if(m_rtp_ch >= 0)
            {
                tcpHeader = (RtpTcpHeader*)(buf+len);
                tcpHeader->dollar = 0x24;
                tcpHeader->channel = m_rtp_ch;
                len += sizeof (RtpTcpHeader);
            }
            RtpHeader* rtpHeader = (RtpHeader*)(buf + len);
            len += sizeof (RtpHeader);

            rtpHeader->version = 2;
            rtpHeader->padding = 0;
            rtpHeader->extension = 0;
            rtpHeader->csrcLen = 0;
            rtpHeader->marker = 1;
            rtpHeader->payloadType = 33;
            rtpHeader->seq = htons(m_media_info[0].seq++);
            rtpHeader->ssrc = htonl(m_media_info[0].ssrc);

            uint64_t pcr = 0;
            int read_ret = m_reader.getTsPKT(buf+len, TSPKTLEN*7,pcr);
            if(read_ret < 0)
            {
                ret = -1;
                break;
            }

            len += read_ret;
            if(read_ret > 0)
            {
                if(tcpHeader != NULL)
                {
                    tcpHeader->len = htons(sizeof (RtpHeader) + read_ret);
                }
                if(m_last_pcr != (uint64_t) - 1 && pcr > m_last_pcr)
                {
                    m_media_info[0].rtp_time += (uint32_t)(pcr - m_last_pcr);
                }
                rtpHeader->timestamp = htonl(m_media_info[0].rtp_time);
                if(m_sock->send(buf,len) < 0)
                {
                    ret = -1;
                    break;
                }
            }
            m_last_pcr = pcr;
            if(m_start_pcr == (uint64_t) - 1)
            {
                m_start_pcr = pcr;
                m_start_ms = getCurrentMs();
                usleep(1000 * 5);
                continue;
            }
            int64_t diff_ms = (pcr - m_start_pcr)/90;
            sleep_ms = int(m_start_ms + diff_ms - getCurrentMs());
            if( sleep_ms > 1000 || sleep_ms < -1000 ){
                m_start_ms = -1;
                m_start_pcr = -1;
                m_last_pcr = -1;
                sleep_ms = sleep_ms > 0 ? 1000 : 5;
            }
            sleep_ms = sleep_ms < 5 ? 5 : sleep_ms;
        }
        usleep(1000 * sleep_ms);
    }
}

int DataSource::getMediaInfo(int mediaIndex, DataSource::MediaInfo &mediaInfo)
{
    if(mediaIndex >= m_mediaNum)
        return -1;
    mediaInfo = m_media_info[mediaIndex];
    return 0;
}

int DataSource::play(Socket *sock, int rtp_ch ,ThreadPool *tp)
{
    m_sock = sock;
    m_rtp_ch = rtp_ch;

    threadpool->append(std::bind(&DataSource::rtpSendFrame,this));
    return 0;
}

int DataSource::playScope(int startSec, int endSec)
{
    if(endSec != -1 && endSec <= m_range)
        m_end_sec = endSec;
    if(startSec != -1 && startSec < m_end_sec)
    {
        m_start_sec = startSec;
        m_reader.seekByTime(m_start_sec);
    }
    return 0;
}

int DataSource::pause()
{
    m_sock = NULL;
    return 0;
}

uint64_t DataSource::getCurrentUs()
{
    struct timeval cur_time;
    gettimeofday( &cur_time, NULL );
    return cur_time.tv_sec*1000000+cur_time.tv_usec;
}

uint64_t DataSource::getCurrentMs()
{
    return getCurrentUs() / 1000;
}

















//#include "datasource.h"

//DataSource::DataSource()
//{
//    memset(m_sdp, 0, sizeof (m_sdp));
//    m_range = 0;
//    m_mediaNum = MAX_MEDIA_NUM;
//    memset(m_mediaInfo, 0, sizeof (m_mediaInfo));
//    m_startSecond = 0;
//    m_endSecond = 0;
//}

//int DataSource::init(const char *fileName)
//{
//    if(m_reader.openFile(fileName) < 0)
//        return -1;
//    m_range = m_reader.getFileRange();
//    m_endSecond = m_range;
//    strncpy(m_mediaInfo[0].track_id, "track1", sizeof (m_mediaInfo[0].track_id));
//    snprintf(m_sdp,sizeof (m_sdp),
//             "v=0\r\n"
//             "o=- 0 1 IN IP4 0.0.0.0\r\n"
//             "s=RTSP Server\r\n"
//             "i=%s\r\n"
//             "t=0 0\r\n"
//             "a=control:*\r\n"
//             "a=range:npt=0-%d\r\n"
//             "m=video 0 RTP/AVP 33\r\n"
//             "a=control:%s\r\n",
//             fileName,m_range,m_mediaInfo[0].track_id);
//    return 0;
//}

//int DataSource::getSdp(char result[])
//{
//    if(m_sdp[0] == 0)
//    {
//        return -1;
//    }
//    memcpy(result,m_sdp,strlen(m_sdp));
//    return 0;
//}

//int DataSource::getRange(int &result)
//{
//    if(m_range == 0)
//        return -1;
//    result = m_range;
//    return 0;
//}

//int DataSource::getMediaNum(int &result)
//{
//    result = m_mediaNum;
//}

//int DataSource::getMediaInfo(int mediaIndex, DataSource::MediaInfo &mediaInfo)
//{
//    if(mediaIndex >= m_mediaNum)
//        return -1;
//    mediaInfo = m_mediaInfo[mediaIndex];
//    return 0;
//}

//int DataSource::getTsPkt(char *buf, int len, uint64_t &pcr)
//{
//    return m_reader.getTsPKT(buf,len,pcr);
//}

//void DataSource::updateRtpTime(uint32_t time)
//{
//    m_mediaInfo[0].rtp_time = time;
//}

//void DataSource::seekFilePosition(int second)
//{
//    m_reader.seekByTime(second);
//}

//int DataSource::playScope(int startSecond, int endSecond)
//{
//    if(endSecond != -1 && endSecond <= m_range)
//        m_endSecond = endSecond;
//    if(startSecond != -1 && startSecond < m_endSecond)
//    {
//        m_startSecond = startSecond;
//        m_reader.seekByTime(m_startSecond);
//    }
//    return 0;
//}

//int DataSource::getEndSecond(int &startSec, int &endSec)
//{
//    startSec = m_startSecond;
//    endSec = m_endSecond;
//}

//void DataSource::updateMediaInfo(DataSource::MediaInfo mediaInfo)
//{
//    m_mediaInfo[0] = mediaInfo;
//}
