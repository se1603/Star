#include "rtspsession.h"
#include <string.h>
#include <sys/time.h>

RtspSession::RtspSession()
{
    memset(m_recvBuff, 0, sizeof(m_recvBuff));
    m_recvLen = 0;
    memset(m_Cseq,0,sizeof (m_Cseq));
    m_rtpChannel = 0;
    memset(m_url, 0, sizeof (m_url));
}

int RtspSession::processSession(int fd, ThreadPool *tp)
{
    m_sock.attachFd(fd);
    m_threadPool = tp;
    while(m_sock.getFd() > 0)
    {
        if(reciveData() < 0)
        {
            printf("ReciveData failed.\n");
            m_sock.closeSocket();
            return -1;
        }
    }
    return 0;
}

int RtspSession::reciveData()
{
    int reciveLen = sizeof(m_recvBuff) - 1 - m_recvLen;
    if(reciveLen <= 0)
    {
        printf("ReciveBuffer have not enough space.\n");
        return -1;
    }
    int ret = m_sock.recive(m_recvBuff + m_recvLen, reciveLen);
    if(ret < 0)
    {
        printf("Recive data failed.\n");
        return -1;
    }
    m_recvLen += ret;

    return handleData();
}

int RtspSession::handleData()
{
    char *reciveBuf = m_recvBuff;
    m_recvBuff[m_recvLen] = '\0';

    int ret = -1;
    while(m_recvLen > 0)
    {
        ret = 0;
        if(*reciveBuf == '$')
        {
            if(m_recvLen <= sizeof (struct RtpTcpHeader))
                break;
            struct RtpTcpHeader* rtpHeader = (struct RtpTcpHeader*)reciveBuf;
            uint32_t rtpLen = ntohs(rtpHeader->len);
            if(m_recvLen < rtpLen + 4)
                break;

            m_recvLen -= rtpLen + 4;
            reciveBuf += rtpLen + 4;
        }
        else
        {
            int parseLen = parseDataLen(reciveBuf, m_recvLen);
            if(parseLen < 0)
                break;
            printClientCmd(reciveBuf, parseLen);
            if(handleCommand(reciveBuf,parseLen) < 0)
                return -1;
            m_recvLen -= parseLen;
            reciveBuf += parseLen;
        }
    }
    if(m_recvLen > 0)
        memmove(m_recvBuff, reciveBuf,m_recvLen);
    return ret;
}

int RtspSession::parseDataLen(const char *data, int len)
{
    const char* start = data;
    const char* endMark = "\r\n\r\n";
    const char* end = NULL;

    end = strstr(start, endMark);
    if(end == NULL)
        return -1;

    int headerLen = end - start + strlen(endMark);

    int contentLen = 0;
    const char* contentMark = "Content-Length ";
    const char* contentStart = strstr(end,contentMark);
    if(contentStart != NULL && strstr(contentStart,"\r\n") != NULL)
        contentLen = atoi(contentStart + strlen(contentMark));

    if(len < (headerLen + contentLen))
        return -1;

    return (headerLen + contentLen);
}

void RtspSession::printClientCmd(const char *data, int len)
{
    char tmp[1024];
    memset(tmp,0,sizeof (tmp));
    memcpy(tmp,data, len > (int)sizeof(tmp) - 1 ? (int)sizeof(tmp) - 1 : len);
    printf("---------------C->S--------------\n");
    printf("%s", tmp);
}

int RtspSession::handleCommand(const char *data, int len)
{
    char method[40];
    RtspMethod rMethod = parseMethod(data);

    if( rMethod == RTSP_METHOD_MAX ){
        printf("Unsupported this method.\n");
        return -1;
    }
    parserCseq(data, len);
    switch(rMethod){
    case RTSP_OPTIONS:
        return handleCmd_OPTIONS();
    case RTSP_SETUP:
        return handleCmd_SETUP(data,len);
    case RTSP_DESCRIBE:
        return handleCmd_DESCRIBE(data,len);
    case RTSP_PLAY:
        return handleCmd_PLAY(data,len);
    case RTSP_TEARDOWN:
        return  handleCmd_TEARDOWN();
    case RTSP_PAUSE:
        return handleCmd_PAUSE();
    }
    return 0;
}

RtspMethod RtspSession::parseMethod(const char *data)
{
    RtspMethod rtsp_method = RTSP_METHOD_MAX;
    if( *data == 'O' && strncmp( data, methods[RTSP_OPTIONS].method_str, strlen(methods[RTSP_OPTIONS].method_str) ) == 0 )
        rtsp_method = RTSP_OPTIONS;
    else if( *data == 'D' && strncmp( data, methods[RTSP_DESCRIBE].method_str, strlen(methods[RTSP_DESCRIBE].method_str) ) == 0 )
        rtsp_method = RTSP_DESCRIBE;
    else if( *data == 'S' && strncmp( data, methods[RTSP_SETUP].method_str, strlen(methods[RTSP_SETUP].method_str) ) == 0 )
        rtsp_method = RTSP_SETUP;
    else if( *data == 'P' && strncmp( data, methods[RTSP_PLAY].method_str, strlen(methods[RTSP_PLAY].method_str) ) == 0 )
        rtsp_method = RTSP_PLAY;
    else if( *data == 'P' && strncmp( data, methods[RTSP_PAUSE].method_str, strlen(methods[RTSP_PAUSE].method_str) ) == 0 )
        rtsp_method = RTSP_PAUSE;
    else if( *data == 'T' && strncmp( data, methods[RTSP_TEARDOWN].method_str, strlen(methods[RTSP_TEARDOWN].method_str) ) == 0 )
        rtsp_method = RTSP_TEARDOWN;
    else if( *data == 'S' && strncmp( data, methods[RTSP_SET_PARAMETER].method_str, strlen(methods[RTSP_SET_PARAMETER].method_str) ) == 0 )
        rtsp_method = RTSP_SET_PARAMETER;
    else if( *data == 'G' && strncmp( data, methods[RTSP_GET_PARAMETER].method_str, strlen(methods[RTSP_GET_PARAMETER].method_str) ) == 0 )
        rtsp_method = RTSP_GET_PARAMETER;
    return rtsp_method;
}

int RtspSession::parserUrl(const char *data, int len)
{
    memset( m_url, 0, sizeof(m_url) );
    const char* url_s_mark = "rtsp://";
    if( getStr( data, len, url_s_mark, " RTSP", m_url, sizeof(m_url)-1 ) < 0 ){
        printf("get url failed\n" );
        return -1;
    }
    return 0;
}

void RtspSession::parserCseq(const char *data, int len)
{
    memset( m_Cseq, 0, sizeof(m_Cseq) );
    getStr( data, len, "CSeq:", "\r\n", m_Cseq, sizeof(m_Cseq)- 1 - strlen("\r\n"));
}

int RtspSession::getStr(const char *data, int len, const char *s_mark, const char *e_mark, char *dest, int dest_len)
{
    const char* satrt = strstr( data, s_mark );
    if( satrt != NULL ){
        const char* end = strstr( satrt, e_mark );
        if( end != NULL )
            strncpy( dest, satrt, end-satrt>dest_len?dest_len:end-satrt );
        return 0;
    }
    return -1;
}

int RtspSession::sendMessage(const char *data, int len)
{
    printf("---------------S->C--------------\n");
    printf("%s", data);
    return m_sock.send(data,len);
}

uint64_t RtspSession::getCurrentUs()
{
    struct timeval cur_time;
    gettimeofday( &cur_time, NULL );
    return cur_time.tv_sec*1000000+cur_time.tv_usec;
}

int RtspSession::handleCmd_OPTIONS()
{
    char sendBuff[512];
    codeMessage(sendBuff,200);

    char result[512];
    sprintf(result,
            "Public: OPTIONS, DESCRIBE, SETUP, PLAY\r\n"
            "\r\n");
    strcat(sendBuff,result);
    return sendMessage(sendBuff,strlen(sendBuff));
}

int RtspSession::handleCmd_SETUP(const char *data, int len)
{
    char sendBuf[512];
    if(strstr(data, "RTP/AVP/TCP") == NULL)
    {
        codeMessage(sendBuf,461);
        char result[512];
        sprintf(result,
                "\r\n");
        strcat(sendBuf,result);
        return sendMessage(sendBuf,strlen(sendBuf));
    }

    const char* interleaved = strstr(data, "interleaved=");
    if(interleaved == NULL)
    {
        codeMessage(sendBuf,400);
        return sendMessage(sendBuf,strlen(sendBuf));
    }

    m_rtpChannel = atoi(interleaved + strlen("interleaved="));

    if(m_rtpChannel < 0)
    {
        codeMessage(sendBuf,400);
        return sendMessage(sendBuf,strlen(sendBuf));
    }

    snprintf(m_session, sizeof(m_session), "Session: %X\r\n",getCurrentUs());
    codeMessage(sendBuf,200);
    char result[512];
    snprintf(result, sizeof(result),
             "%s"
             "Transport: RTP/AVP/TCP;unicast;interleaved=%d-%d\r\n\r\n",
             m_session, m_rtpChannel, m_rtpChannel + 1);
    strcat(sendBuf,result);
    return sendMessage(sendBuf,strlen(sendBuf));
}

int RtspSession::handleCmd_DESCRIBE(const char *data, int len)
{
    char sendBuf[512];
    if(parserUrl(data, len) < 0)
    {
        codeMessage(sendBuf,400);
        return sendMessage(sendBuf,strlen(sendBuf));
    }

    char *fileName = strstr(strstr(m_url,"rtsp://") + strlen("rtsp://"), "/") + 1;

    if(m_dataSource.init(fileName) < 0)
    {
        codeMessage(sendBuf,404);
        return sendMessage(sendBuf,strlen(sendBuf));
    }

    //    char sdp[1024];
    //    memset(sdp,0,sizeof (sdp));
    //    m_dataSource.getSdp(sdp);
    const char *sdp = m_dataSource.getSdp();

    codeMessage(sendBuf,200);
    char result[512];

    sprintf(result, "Content-Base: %s\r\n"
                    "Content-type: application/sdp\r\n"
                    "Content-length: %d\r\n\r\n"
                    "%s",
            m_url,
            strlen(sdp),
            sdp);
    strcat(sendBuf,result);
    return sendMessage(sendBuf,strlen(sendBuf));
}

int RtspSession::handleCmd_PLAY(const char *data, int len)
{
    int range = 0;
    range = m_dataSource.getRange();
    int startSec = 0;
    int endSec = range;

    const char* rangeStr = strstr(data, "Range: npt=");
    if(rangeStr != NULL)
    {
        startSec = atoi(rangeStr + strlen("Range: npt="));
        const char* endSecPos = strstr(rangeStr + strlen("Range: npt="),"-");
        if(endSecPos != NULL)
        {
            int sec = atoi(endSecPos + 1);
            if(sec != 0)
                endSec = sec;
        }
    }
    m_dataSource.playScope(startSec,endSec);
    DataSource::MediaInfo mediaInfo;
    m_dataSource.getMediaInfo(0,mediaInfo);
    char sendBuf[512];
    codeMessage(sendBuf,200);
    char result[512];
    snprintf(result, sizeof (result),
             "Range: npt=%d.000-%d.000\r\n"
             "RTP-Info: url=%s/%s;seq=%d;rtptime=%u\r\n\r\n",
             startSec,endSec,m_url,mediaInfo.track_id,mediaInfo.seq,mediaInfo.rtp_time);
    strcat(sendBuf,result);
    if(sendMessage(sendBuf,strlen(sendBuf)) < 0)
    {
        return -1;
    }

//    return m_rtpSession.play(&m_sock,m_rtpChannel,&m_dataSource/*,m_threadPool*/);
    return m_dataSource.play(&m_sock,m_rtpChannel,m_threadPool);
}

int RtspSession::handleCmd_PAUSE()
{
//    m_rtpSession.pause();
    m_dataSource.pause();
    char sendBuf[512];
    codeMessage(sendBuf,200);
    char result[512];
    sprintf(result,
            "\r\n");
    strcat(sendBuf,result);
    sendMessage(sendBuf,strlen(sendBuf));
    return 0;
}

int RtspSession::handleCmd_TEARDOWN()
{
    char sendBuf[512];
    codeMessage(sendBuf,200);
    char result[512];
    sprintf(result,
            "\r\n");
    strcat(sendBuf,result);
    sendMessage(sendBuf,strlen(sendBuf));
    m_sock.closeSocket();
    return 0;
}

void RtspSession::codeMessage(char *result, int code)
{
    int i = 0;
    for(; ; i++)
    {
        if(code == codes[i].code)
            break;
        else if(codes[i].code == 0)
        {
            i = 2;
            break;
        }
    }

    sprintf(result,"RTSP/1.0 %d %s\r\n"
                   "%s\r\n",
            codes[i].code,codes[i].code_str,m_Cseq);
}
