#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "socket.h"

class TcpSocket : public Socket
{
public:
    TcpSocket();
    ~TcpSocket();

    int connect(const char* ip, int port);
    int send(const char *buf, int len);
    int recive(char *buf, int len);
};

#endif // TCPSOCKET_H
