#ifndef RTSPSERVER_H
#define RTSPSERVER_H

#include <map>
#include <rtspsession.h>

class RtspServer : public Socket
{
public:
    RtspServer();
    ~RtspServer();

    int start(const char *ip, int port);
    int acceptClient(int sockfd, char *ip, int *port);
    int processClient(int fd, ThreadPool *tp);

private:
    ThreadPool threadPool;
    std::map<int, RtspSession*> m_sessionMap;
};

#endif // RTSPSERVER_H
