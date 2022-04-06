//#ifndef RTPSESSION_H
//#define RTPSESSION_H

//#include "datasource.h"
//#include "rtsprtpdefine.h"
//#include "socket.h"

//class RtpSession
//{
//public:
//    RtpSession();

//    int play(Socket* sock, int rtpChannel, DataSource *ds);
//    int pause();
//    void sendRTPPacket();
//    int playScope(int startSecond, int endSecond);

//    static uint64_t getCurrentUs(); //获取系统运行至此时的微秒时间
//    static uint64_t getCurrentMs(); //获取系统运行至此时的毫秒时间

//private:
//    uint64_t m_startPcr;   //起始时间戳
//    uint64_t m_startMs;
//    uint64_t m_lastPcr;    //结束时间戳

//    int m_startSecond;   //视频起始秒
//    int m_endSecond;  //视频结束秒

//    DataSource::MediaInfo m_mediaInfo;

//    Socket *m_sock;
//    int m_rtpChannel;   // < 0 RTP OVER UDP; >= 0 RTP OVER RTSP
//    DataSource *m_dataSource;
//    ThreadPool *m_threadPool;
//};

//#endif // RTPSESSION_H
