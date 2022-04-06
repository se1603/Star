#include "tcpsocket.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

TcpSocket::TcpSocket()
{

}

TcpSocket::~TcpSocket()
{

}

int TcpSocket::connect(const char *ip, int port)
{
    if(createSocket(SOCK_STREAM) < 0)
        return -1;
    setBlock(true);
    struct sockaddr_in remote;
    if(setAddr(ip,port,remote) < 0)
        return -1;
    if(::connect(m_fd,(struct sockaddr *)&remote, sizeof (struct sockaddr)) == -1)
    {
        printf("Connect failed. Errorn info: %d %s\n",errno,strerror(errno));
        return -1;
    }
    setBlock(false);
    return 0;
}

int TcpSocket::send(const char *buf, int len)
{
    if(buf == NULL || len <= 0)
        return -1;
    int ret = ::send(m_fd,buf,len,0);
    if(ret < 0)
    {
        if(errno == EWOULDBLOCK || errno == EINTR || errno == EWOULDBLOCK)
            return 0;
        return -1;
    }
    return ret;
}

int TcpSocket::recive(char *buf, int len)
{
    if(buf == NULL || len <= 0)
        return -1;
    int ret = recv(m_fd,buf,len,0);
    if(ret < 0)
    {
        if(errno == EWOULDBLOCK || errno == EINTR || errno == EWOULDBLOCK)
            return 0;
        return -1;
    }
    return ret;
}
