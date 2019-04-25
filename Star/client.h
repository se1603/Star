#ifndef CLIENT_H
#define CLIENT_H

#include "network.h"
#include <string>
#include "json/json.h"

struct File_info{
    typedef unsigned long long Size_type;
    size_t filename_size;  //文件名的长度
    Size_type filesize;    //文件的大小
    File_info() : filename_size(0), filesize(0){}
};

class Client
{
public:
    Client();

    void connectServer();
    void getFile();
    bool sendMessage(std::string message);

    void receiveFile(std::string message);
    void receiveFilename(boost::system::error_code &e,boost::asio::ip::udp::endpoint sender_ep,socket_ptr udpsock);
     void receive_file_content();   //写文件

private:
    //文件
    FILE *fp;
    File_info file_info;
    File_info::Size_type total_bytes_writen;
    static const unsigned buffer_size = 100 * 1024;
    char buffer[buffer_size];
};

#endif // CLIENT_H
