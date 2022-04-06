#include "socket.h"
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

Socket::Socket()
{
    m_fd = INVALID_SOCKET_FD;
}

Socket::~Socket()
{
    closeSocket();
}

void Socket::closeSocket()
{
    if(m_fd != INVALID_SOCKET_FD)
    {
        close(m_fd);
        m_fd = INVALID_SOCKET_FD;
    }
}

int Socket::getFd() const
{
    return m_fd;
}

int Socket::attachFd(int fd)
{
    if(m_fd != INVALID_SOCKET_FD)
        return -1;
    else
        m_fd = fd;
    return 0;
}

int Socket::detachFd()
{
    int tmp = m_fd;
    m_fd = INVALID_SOCKET_FD;
    return tmp;
}

int Socket::createSocket(int socketType)
{
    closeSocket();
    m_fd = socket(AF_INET, socketType, 0);
    if(m_fd == -1)
    {
        printf("Create socket failed. Errorn info: %d %s\n",errno,strerror(errno));
        return -1;
    }
    return m_fd;
}

int Socket::bindSocket(const char *ip, int port)
{
    struct sockaddr_in localAddr;
    if(setAddr(ip,port,localAddr) < 0)
        return -1;
    if(bind(m_fd,(struct sockaddr *)&localAddr,sizeof(localAddr)) == -1)
    {
        printf("Bind socket failed. Errorn info: %d %s\n",errno,strerror(errno));
        return -1;
    }
    return 0;
}

int Socket::setAddr(const char *ip, int port, sockaddr_in &addr)
{
    int ipNumber = 0;
    if(ip == NULL || ip[0] == '\0')
        ipNumber = 0;
    else if(inet_addr(ip) == INADDR_NONE)
    {
        struct hostent *h = NULL;
        if((h = gethostbyname(ip)) == NULL)
        {
            printf("Get host by name failed, name:%s\n", ip);
            return -1;
        }
        memcpy(&ipNumber, *(h->h_addr_list),sizeof (ipNumber));
    }
    else
    {
        ipNumber = inet_addr(ip);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = ipNumber;
    return 0;
}

int Socket::setAddrReuse()
{
    int opt = 1;
    if(setsockopt(m_fd,SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof (opt)) < 0)
    {
        printf("Set reuseaddr failed. Errorn info: %d %s\n",errno,strerror(errno));
        return -1;
    }
    return 0;
}

int Socket::setBlock(bool isBlock)
{
    if(m_fd == INVALID_SOCKET_FD)
        return 0;
    int flags = fcntl(m_fd,F_GETFL);
    if(flags < 0)
    {
        printf("Set socket block failed! %s\n",strerror(errno));
        return -1;
    }

    if(isBlock)
        flags &= ~O_NONBLOCK;
    else
        flags |= O_NONBLOCK;
    int returnVal = fcntl(m_fd,F_SETFL,flags);
    if(returnVal < 0)
    {
        printf("Set socket block failed! %s\n",strerror(errno));
        return -1;
    }
    return 0;
}
