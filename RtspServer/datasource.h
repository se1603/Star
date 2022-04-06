#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "tsfilereader.h"
#include "socket.h"
#include "rtsprtpdefine.h"
#include "threadpool.h"

#define MAX_MEDIA_NUM 1

class DataSource
{
public:
    DataSource();

    struct MediaInfo{
        char track_id[32];
        uint16_t seq;
        uint32_t rtp_time;
        uint32_t ssrc;
    };

    int init(const char* fileName);
    const char* getSdp();
    int getRange();
    int getMediaNum();
    int getMediaInfo(int mediaIndex, MediaInfo& mediaInfo);
    int play(Socket* sock, int rtp_ch, ThreadPool *tp);
    int playScope(int startSec,int endSec);
    int pause();
    void rtpSendFrame();

    uint64_t getCurrentUs(); //获取系统运行至此时的微秒时间
    uint64_t getCurrentMs(); //获取系统运行至此时的毫秒时间
private:
    char m_sdp[1024 * 2];
    int m_range;
    int m_mediaNum;

    MediaInfo m_media_info[MAX_MEDIA_NUM];
    int m_start_sec;   //起始秒
    int m_end_sec;   //结束秒

    int m_rtp_ch;    //rtp_ch < 0 RTP OVER UDP; rtp_ch >= 0 RTP OVER RTSP

    TsFileReader m_reader;
    Socket *m_sock;

    uint64_t m_start_pcr;  //起始时间戳
    uint64_t m_start_ms;
    uint64_t m_last_pcr;   //结束时间戳

    ThreadPool *threadpool;
};

//#include "tsfilereader.h"
//#include <string.h>

//#define MAX_MEDIA_NUM 1

//class DataSource
//{
//public:
//    DataSource();

//    struct MediaInfo{
//        char track_id[32];
//        uint16_t seq;
//        uint32_t rtp_time;
//        uint32_t ssrc;
//    };

//    int init(const char* fileName);
//    int getSdp(char result[]);
//    int getRange(int &result);
//    int getMediaNum(int &result);
//    int getMediaInfo(int mediaIndex, MediaInfo& mediaInfo);
//    int getTsPkt(char *buf, int len, uint64_t &pcr);
//    void updateRtpTime(uint32_t time);
//    void seekFilePosition(int second);
//    int playScope(int startSecond, int endSecond);
//    int getEndSecond(int &startSec, int &endSec);
//    void updateMediaInfo(MediaInfo mediaInfo);

//private:
//    MediaInfo m_mediaInfo[MAX_MEDIA_NUM];
//    char m_sdp[1024 * 2];  //视频sdp信息
//    int m_range;   //视频范围
//    int m_mediaNum;

//    int m_startSecond;   //视频起始秒
//    int m_endSecond;  //视频结束秒

//    TsFileReader m_reader;
//};

#endif // DATASOURCE_H
