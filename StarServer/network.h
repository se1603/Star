/* Author:王梦娟
 * Date:2019-4-25
 * Note:封装了消息，文件的接收和发送
*/
#ifndef NETWORK_H
#define NETWORK_H

#include <boost/asio.hpp>

#define BUFFERSIZE 512
#define MAXLENGTH 512

typedef boost::shared_ptr<boost::asio::ip::udp::socket> socket_ptr;
typedef boost::asio::ip::udp::endpoint endpoint;

struct PackageHead{
    int count;  //包总数
    unsigned int index;       //包序号
    unsigned int len;   //数据字节数
    unsigned int crc32val;   //校验码
    int errorFlag;   //错误码
};

struct Package{
    PackageHead head;
    char buff[BUFFERSIZE];
};

class NetWork
{
public:
    NetWork(socket_ptr s);

    int sendto(std::string message, endpoint ep);
    std::string receive(boost::asio::ip::udp::endpoint &sender_ep);

    long int sendFile(FILE *fp, endpoint ep);

private:
    socket_ptr sock;
};

#endif // NETWORK_H
