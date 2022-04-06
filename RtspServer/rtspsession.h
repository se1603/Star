#ifndef RTSPSESSION_H
#define RTSPSESSION_H

//#include "rtpsession.h"
#include "tcpsocket.h"
#include "datasource.h"

#define MAX_BUFFER_LEN 1024 * 4

class RtspSession
{
public:
    RtspSession();

    int processSession(int fd, ThreadPool *tp);
    int reciveData();
    int handleData();
    int parseDataLen(const char* data, int len);    //解析消息长度
    void printClientCmd(const char* data, int len);    //打印客户端命令
    int handleCommand(const char* data, int len);   //处理命令
    RtspMethod parseMethod(const char* data);    //解析方法
    int parserUrl(const char* data, int len);
    void parserCseq( const char* data, int len );
    int getStr( const char* data, int len, const char* s_mark, const char* e_mark, char* dest, int dest_len );
    int sendMessage(const char* data, int len);

    uint64_t getCurrentUs(); //获取系统运行至此时的微秒时间
private:
    int handleCmd_OPTIONS();
    int handleCmd_SETUP(const char* data, int len);
    int handleCmd_DESCRIBE(const char* data, int len);
    int handleCmd_PLAY(const char* data, int len);
    int handleCmd_PAUSE();
    int handleCmd_TEARDOWN();
    void codeMessage(char* result, int code);

    TcpSocket m_sock;
    DataSource m_dataSource;
//    RtpSession m_rtpSession;
    char m_recvBuff[MAX_BUFFER_LEN];
    uint32_t m_recvLen;

    int m_rtpChannel;  //RTP OVER TCP时的通道
    char m_url[256];   //Rtsp地址
    char m_session[128];
    char m_Cseq[128];
    ThreadPool *m_threadPool;
};

#endif // RTSPSESSION_H
