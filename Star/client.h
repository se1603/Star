#ifndef CLIENT_H
#define CLIENT_H

#include "network.h"
#include <string>
#include "json/json.h"
#include "audience.h"
#include <QObject>

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
    Client(QObject* parent=0);

    void splictString(std::string &s, std::vector<std::string> &v, const std::string &c);

    void connectServer();
    void getFile();
    socket_ptr sendMessage(std::string message);

    void receiveFile(std::string message);
    void receiveFilename(boost::system::error_code &e,boost::asio::ip::udp::endpoint sender_ep,socket_ptr udpsock);
    void receive_file_content();   //写文件

    //关于观众信息的函数（在QML端调用）
    Q_INVOKABLE void sendLoginInfo(QString n,QString p);
    Q_INVOKABLE void sendRegisterInfo(QString n,QString p);
    Q_INVOKABLE QString getMyaudience();
    Q_INVOKABLE void loginOut(QString n);
    Q_INVOKABLE void updateAvatar(QString n,QString audienceName);

signals:
    void loginsucceed();
    void loginfailed();
    void registesucceed();
    void registefailed();
    void loginout();
    void haslogined();
    void updateAvatarFailed();
    void updateAvatarSucceed();
private:
    //文件
    FILE *fp;
    File_info file_info;
    File_info::Size_type total_bytes_writen;
    static const unsigned buffer_size = 100 * 1024;
    char buffer[buffer_size];

    Audience* _audience;
};

#endif // CLIENT_H
