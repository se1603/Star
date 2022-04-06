//#include "rtpsession.h"
//#include <sys/time.h>
//#include <unistd.h>

//RtpSession::RtpSession()
//{
//    m_sock = NULL;
//    m_rtpChannel = 0;
//    m_threadPool = new ThreadPool(1);

//    m_startSecond = 0;
//    m_endSecond = 0;
//    m_startPcr = -1;
//    m_startMs = -1;
//    m_lastPcr = -1;
//}

//int RtpSession::play(Socket *sock, int rtpChannel, DataSource *ds/*, ThreadPool *tp*/)
//{
//    m_threadPool = tp;
//    m_dataSource = ds;
//    m_sock = sock;
//    m_rtpChannel = rtpChannel;
//    m_dataSource->getEndSecond(m_startSecond,m_endSecond);
//    m_dataSource->getMediaInfo(0,m_mediaInfo);
//    m_threadPool->append(std::bind(&RtpSession::sendRTPPacket,this));
//    tp->append(std::bind(&RtpSession::sendRTPPacket,this));
//    return 0;
//}

//int RtpSession::pause()
//{
//    m_sock = NULL;
//    return 0;
//}

//void RtpSession::sendRTPPacket()
//{
//    int ret = 0;
//    while(1)
//    {
//        int sleep_ms = 5;
//        if(m_sock != NULL)
//        {
//            char buf[TSPKTLEN * 7 + sizeof (RtpTcpHeader) + sizeof (RtpHeader)] = "";
//            int len = 0;
//            RtpTcpHeader* tcpHeader = NULL;
//            if(m_rtpChannel >= 0)
//            {
//                tcpHeader = (RtpTcpHeader*)(buf+len);
//                tcpHeader->dollar = 0x24;
//                tcpHeader->channel = m_rtpChannel;
//                len += sizeof (RtpTcpHeader);
//            }
//            RtpHeader* rtpHeader = (RtpHeader*)(buf + len);
//            len += sizeof (RtpHeader);

//            rtpHeader->version = 2;
//            rtpHeader->padding = 0;
//            rtpHeader->extension = 0;
//            rtpHeader->csrcLen = 0;
//            rtpHeader->marker = 1;
//            rtpHeader->payloadType = 33;
//            rtpHeader->seq = htons(m_mediaInfo.seq++);
//            rtpHeader->ssrc = htonl(m_mediaInfo.ssrc);

//            uint64_t pcr = 0;
//            int readRet = m_dataSource->getTsPkt(buf + len,TSPKTLEN*7,pcr);
//            if(readRet < 0)
//            {
//                ret = -1;
//                break;
//            }

//            len += readRet;
//            if(readRet > 0)
//            {
//                if(tcpHeader != NULL)
//                {
//                    tcpHeader->len = htons(sizeof (RtpHeader) + readRet);
//                }
//                if(m_lastPcr != (uint64_t) - 1 && pcr > m_lastPcr)
//                {
//                    m_mediaInfo.rtp_time += (uint32_t)(pcr - m_lastPcr);
//                }
//                rtpHeader->timestamp = htonl(m_mediaInfo.rtp_time);
//                if(m_sock->send(buf,len) < 0)
//                {
//                    ret = -1;
//                    break;
//                }
//            }
//            m_lastPcr = pcr;
//            if(m_startPcr == (uint64_t) - 1)
//            {
//                m_startPcr = pcr;
//                m_startMs = getCurrentMs();
//                usleep(1000 * 5);
//                continue;
//            }
//            int64_t diff_ms = (pcr - m_startPcr) / 90;
//            sleep_ms = int(m_startMs + diff_ms - getCurrentMs());
//            if( sleep_ms > 1000 || sleep_ms < -1000 ){
//                m_startMs = -1;
//                m_startPcr = -1;
//                m_lastPcr = -1;
//                sleep_ms = sleep_ms > 0 ? 1000 : 5;
//            }
//            sleep_ms = sleep_ms < 5 ? 5 : sleep_ms;

//        }
//        usleep(1000 * sleep_ms);
//    }
//}

//int RtpSession::playScope(int startSecond, int endSecond)
//{
//    m_dataSource->playScope(startSecond,endSecond);
//    m_dataSource->getEndSecond(m_startSecond,m_endSecond);
//    return 0;
//}

//uint64_t RtpSession::getCurrentUs()
//{
//    struct timeval cur_time;
//    gettimeofday( &cur_time, NULL );
//    return cur_time.tv_sec*1000000+cur_time.tv_usec;
//}

//uint64_t RtpSession::getCurrentMs()
//{
//    return getCurrentUs() / 1000;
//}
