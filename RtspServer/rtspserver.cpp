#include "rtspserver.h"
#include <string.h>
#include <dirent.h>

RtspServer::RtspServer()
{
    std::string advertsPath = "mkdir ./adverts";
    system(advertsPath.c_str());
    std::string videosPath = "mkdir ./videos";
    system(videosPath.c_str());
}

RtspServer::~RtspServer()
{

}

int RtspServer::start(const char *ip, int port)
{
    closeSocket();

    if(createSocket(SOCK_STREAM) < 0)
        return -1;
    if(setAddrReuse() < 0 || bindSocket(ip,port) < 0)
    {
        closeSocket();
        return -1;
    }

    if(listen(m_fd, 128) == -1)
    {
        closeSocket();
        printf("Failed to listen.\n");
        return -1;
    }

    printf("Start RTSP Server success! Listen port: %d\n", port);
    printf("Play streams from this server using the URL "
           "rtsp://%s:%d/<filename>\n"
           "where <filename> is a file which type is "
           "inferred from its name suffix: \".ts\"\n"
           "\r\n",ip,port);

    while(1)
    {
        int clientSockFd;
        char clientIp[40];
        int clientPort;

        clientSockFd = acceptClient(m_fd,clientIp,&clientPort);
        if(clientSockFd < 0)
        {
            printf("failed to accept client\n");
            return -1;
        }
        printf("accept client;client ip:%s,client port:%d\n", clientIp, clientPort);
        threadPool.append(std::bind(&RtspServer::processClient, this, clientSockFd,&threadPool));
    }
}

int RtspServer::acceptClient(int sockfd, char *ip, int *port)
{
    int clientfd;
    socklen_t len = 0;
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    len = sizeof(addr);

    clientfd = accept(sockfd, (struct sockaddr *)&addr, &len);
    if(clientfd < 0)
        return -1;

    strcpy(ip, inet_ntoa(addr.sin_addr));
    *port = ntohs(addr.sin_port);

    return clientfd;
}

int RtspServer::processClient(int fd, ThreadPool *tp)
{
    RtspSession* session = new RtspSession;
    m_sessionMap[fd] = session;
    session->processSession(fd,tp);
    return 0;
}
