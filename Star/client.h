#ifndef CLIENT_H
#define CLIENT_H

#include "network.h"
#include <string>
#include "json/json.h"
#include <QObject>
#include "movieandtelevision.h"

struct File_info{
    typedef unsigned long long Size_type;
    size_t filename_size;  //文件名的长度
    Size_type filesize;    //文件的大小
    File_info() : filename_size(0), filesize(0){}
};

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject *p = 0);

    void connectServer();

    socket_ptr sendMessage(std::string message);

    std::vector<std::string> jsonParse(char message[]);
    Q_INVOKABLE QString browseFilm(int category, int type);
    Q_INVOKABLE QString showCategory(int type);

    //获取文件
    void getFile();
    void receiveFile(std::string message);
    void receiveFilename(boost::system::error_code &e,boost::asio::ip::udp::endpoint sender_ep,socket_ptr udpsock);
    void receive_file_content();

private:
    //缓存
    std::map<int,std::map<int,std::vector<MovieAndTelevision>>> movieAndTelevision;
    //文件
    FILE *fp;
    File_info file_info;
};

#endif // CLIENT_H
