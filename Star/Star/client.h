#ifndef CLIENT_H
#define CLIENT_H

#include "network.h"
#include <string>
#include "json/json.h"
#include <QObject>
#include "movieandtelevision.h"
#include "audience.h"

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
    void splictString(std::string &s, std::vector<std::string> &v, const std::string &c);

    //显示影视
    Q_INVOKABLE QString browseMovieAndTelevision(int category, int type); //浏览影视
    Q_INVOKABLE QString showCategory(int type);  //显示分类
    Q_INVOKABLE QString showRecommend(int category);  //显示各个页面的推荐影视

    Q_INVOKABLE QString getMovieInfo(QString n,int i);//获取影视信息
    //获得演员和导演信息
    Q_INVOKABLE QString getActorInfo(QString n);

    //用户操作（QML端）
    //登录
    Q_INVOKABLE void sendLoginInfo(QString n,QString p);
    //注册
    Q_INVOKABLE void sendRegisterInfo(QString n,QString p);
    //退出
    Q_INVOKABLE void loginOut(QString n);
    //修改头像
    Q_INVOKABLE void updateAvatar(QString n, QString a);
    //获取收藏
    Q_INVOKABLE QString audienceCollection(QString name);
    //获取记录
    Q_INVOKABLE QString audienceRecord(QString name);
    //添加收藏
    Q_INVOKABLE void addCollection(QString name, QString collecttime, QString videoname, QString type);
    //用户类函数（C++端）
    void getAudienceInfo(std::string name);

    //获取文件
    void getFile();
    void receiveFile(std::string message);
    void receiveFilename(boost::system::error_code &e,boost::asio::ip::udp::endpoint sender_ep,socket_ptr udpsock);
    void receive_file_content();

signals:
    void loginsucceed(QString name,QString avatar);
    void loginfailed();
    void registesucceed();
    void registefailed();
    void loginout();
    void haslogined();
    void updateAvatarFailed();
    void updateAvatarSucceed(QString newsource);
    void collectsucceed();
    void collectfailed();
private:
    //文件
    FILE *fp;
    File_info file_info;
    Audience* _audience;
    std::map<int,std::map<int,std::string>> interfaceBuffer;
    std::map<int,std::string> categoryBuffer;
    std::map<int,std::string> recommendBuffer;
};

#endif // CLIENT_H
