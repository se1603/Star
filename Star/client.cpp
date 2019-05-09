#include "client.h"
#include <iostream>
#include <qdebug.h>
#include "film.h"
#include <dirent.h>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint serverep(boost::asio::ip::address::from_string("192.168.30.210"),8001);
boost::asio::ip::udp::socket udpsock(service,boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),7788));


Client::Client(QObject *p) :
    QObject(p)
{
    connectServer();
    _audience = new Audience();
}

void Client::splictString(std::string &s, std::vector<std::string> &v, const std::string &c)
{
    std::string::size_type pos1,pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2){
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

void Client::connectServer()
{
    getFile();
//    showRecommend(1);
//    browseFilm(1,6);
}

void Client::getFile()
{
    std::string path = "./posts";
    DIR * dir;
    dir = opendir(path.data());
    if(dir == nullptr )
    {
        Json::Value root;
        root["request"] = "FILETRANSFER";
        root["fileName"] = "posts.tar.gz";
        root.toStyledString();
        std::string message = root.toStyledString();

        receiveFile(message);

        std::string commend = "tar xzvf posts.tar.gz";
        system(commend.c_str());
    }
}

socket_ptr Client::sendMessage(std::string message)
{
    std::cout << "Send message:"  << message << std::endl;
    //创建一个新的套接字。
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    boost::asio::ip::udp::endpoint sender_ep;

    NetWork sock(udpsock);

    sock.sendto(message,serverep);
    return  udpsock;
}

QString Client::browseMovieAndTelevision(int category,int type)
{
    Json::Value qmlvalue;
    bool sendRequest = true;

    //先在缓存中找
    if(movieAndTelevision.find(category) != movieAndTelevision.end())
    {
        std::map<int,std::vector<MovieAndTelevision>> m1 = movieAndTelevision[category];
        if(m1.find(type) != m1.end())
        {
            sendRequest = false;
            std::vector<MovieAndTelevision> films = m1[type];
            for(int i = 0;i != films.size(); i++)
            {
                Json::Value item;
                item["name"] = films[i].name();
                item["post"] = films[i].post();
                qmlvalue.append(item);
            }
        }
    }
    if(sendRequest)
    {
        Json::Value root;
        root["request"] = "INTERFACE";
        root["interface"] = std::to_string(category) ;    //电影
        root["type"] = std::to_string(type);  //类型
        root.toStyledString();
        std::string message = root.toStyledString();

        socket_ptr udpsock;
        udpsock = sendMessage(message);

        NetWork sock(udpsock);

        Json::Value value;
        Json::Reader reader;
        std::string res = sock.receive();

        std::vector<MovieAndTelevision> films;

        if(!reader.parse(res,value))
        {
            std::cerr << "Parse message failed." << std::endl;
        }
        else
        {
            const Json::Value arrayObj = value["movieAndTelevision"];
            for (unsigned int i = 0; i < arrayObj.size(); i++)
            {
                std::string name = arrayObj[i]["name"].asString();
                std::string post = arrayObj[i]["post"].asString();

                MovieAndTelevision m;
                m.setName(name);
                m.setPost(post);
                films.push_back(m);
            }
            qmlvalue = value["movieAndTelevision"];

            int interface = value["interface"].asInt();
            int type = value["type"].asInt();

            if(movieAndTelevision.find(interface) == movieAndTelevision.end())
            {
                std::map<int,std::vector<MovieAndTelevision>> m1;
                m1[type] = films;
                movieAndTelevision[interface] = m1;
            }
            else
            {
                std::map<int,std::vector<MovieAndTelevision>> m1;
                m1 = movieAndTelevision[interface];
                if(m1.find(type) == m1.end())
                {
                    m1[type] = films;
                }
            }
        }
    }

    std::cout << qmlvalue.toStyledString() << std::endl;

    QString t = QString::fromStdString(qmlvalue.toStyledString());
    return t;
}

QString Client::showCategory(int type)
{
    Json::Value root;
    root["request"] = "CATEGORY";
    root["type"] = std::to_string(type);
    root.toStyledString();
    std::string message = root.toStyledString();

    socket_ptr udpsock;
    udpsock = sendMessage(message);

    NetWork sock(udpsock);

    Json::Value value;
    Json::Value qmlvalue;
    Json::Reader reader;
    std::string res = sock.receive();

    if(!reader.parse(res,value))
    {
        std::cerr << "Receive message failed." << std::endl;
    }
    else
    {
        qmlvalue = value["categorys"];
    }
    qmlvalue.toStyledString();
    std::cout << qmlvalue.toStyledString() << std::endl;

    QString t = QString::fromStdString(qmlvalue.toStyledString());
    return t;
}

QString Client::showRecommend(int category)
{
    Json::Value root;
    root["request"] = "RECOMMEND";
    root["category"] = std::to_string(category);
    root.toStyledString();
    std::string message = root.toStyledString();

    socket_ptr udpsock;
    udpsock = sendMessage(message);

    NetWork sock(udpsock);

    std::string res = sock.receive();

    Json::Value value;
    Json::Value qmlvalue;
    Json::Reader reader;
    if(!reader.parse(res,value))
    {
        std::cerr << "Receive message failed." << std::endl;
    }
    else
    {
//        const Json::Value arrayObj = value["recommends"];
//        Json::Value titleObj;
//        for (unsigned int i = 0; i < arrayObj.size(); i++)
//        {
//            Json::Value item;
//            std::string title = arrayObj[i]["title"].asString();
//            item["title"] = arrayObj[i]["title"];
//            std::cout << title << std::endl;
//            titleObj.append(item);
//        }
        qmlvalue["secondRecommends"] = value["secondRecommends"];
        qmlvalue["firstRecommends"] = value["firstRecommends"];
    }
    std::cout << qmlvalue.toStyledString() << std::endl;
    QString t = QString::fromStdString(qmlvalue.toStyledString());
    return t;
}

void Client::receiveFile(std::string message)
{
    std::cout << "Send message:"  << message << std::endl;
    //创建一个新的套接字。
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    boost::asio::ip::udp::endpoint sender_ep;

    NetWork sock(udpsock);

    sock.sendto(message,serverep);

    std::cout << "======Receive file size======" << std::endl;

    udpsock->receive_from(boost::asio::buffer(reinterpret_cast<char*>(&file_info), sizeof(file_info)),sender_ep);  //接收文件大小

    std::cout << "filename: " << file_info.filename_size << std::endl;
    if(file_info.filename_size == 0){
        std::cout << "The file doesn't exit." << std::endl;
        return;
    }
    boost::system::error_code error;
    receiveFilename(error,sender_ep,udpsock);
}

void Client::receiveFilename(boost::system::error_code &e,boost::asio::ip::udp::endpoint sender_ep,socket_ptr udpsock)
{
    std::cout << "======Receive fileName======" << std::endl;
    if(e)
    {
        std::cout << boost::system::system_error(e).what() << std::endl;
    }

    int len = file_info.filename_size;
    char filename[len];
    memset(filename,0,sizeof (char) * len);

    //    boost::asio::ip::udp::endpoint sender_ep;

    udpsock->receive_from(boost::asio::buffer(filename,len),sender_ep); //接收文件名

    std::cout << filename << std::endl;

    fp = fopen(filename, "wb");
    if (fp == NULL) {
        std::cerr << "Failed to open file to write\n";
        return;
    }

    NetWork sock(udpsock);

    sock.receiveFile(fp);

    //    receive_file_content();
}

void Client::receive_file_content()
{
    std::cout << "=====Receive File Context=====" << std::endl;
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    NetWork sock(udpsock);

    sock.receiveFile(fp);
}

void Client::sendLoginInfo(QString n, QString p)
{
    //qDebug() << name << password;
    std::string aN = n.toStdString();
    std::string aPW = p.toStdString();

    Json::Value audience;
    audience["request"] = "VERIFYINFO";
    audience["name"] = aN;
    audience["password"] = aPW;
    audience.toStyledString();
    std::string message = audience.toStyledString();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);


    NetWork sock(udpsockptr);
    std::string m;

    m = sock.receive();
    if(m == "LOGINSUCCEED"){
        emit loginsucceed();
    }else if(m == "VERIFYFAILED"){
        emit loginfailed();
    }else if(m == "HASLOGINED"){
        emit haslogined();
    }
}

void Client::sendRegisterInfo(QString n, QString p)
{
    std::string rN = n.toStdString();
    std::string rPW = p.toStdString();

    Json::Value registor;
    registor["request"] = "REGISTEACCOUNT";
    registor["name"] = rN;
    registor["password"] = rPW;
    registor.toStyledString();
    std::string message = registor.toStyledString();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);

    NetWork sock(udpsockptr);
    std::string m;

    m = sock.receive();
    std::cout << m << std::endl;
    if(m == "REGISTESUCCEED"){
        emit registesucceed();
    }else{
        emit registefailed();
    }
}

void Client::loginOut(QString n)
{
    Json::Value logOUT;
    logOUT["request"] = "LOGOUT";
    logOUT["name"] = n.toStdString();
    logOUT.toStyledString();

    std::string message = logOUT.toStyledString();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);

    NetWork sock(udpsockptr);
    std::string m;

    m = sock.receive();

    if(m == "LOGOUTSUCCEED"){
        _audience = nullptr;
        emit loginout();
    }
}

void Client::updateAvatar(QString n,QString a)
{
    auto filename = n.toStdString();
    auto audiencename = a.toStdString();
    std::cout << audiencename << filename << std::endl;

    Json::Value AVATAR;
    AVATAR["request"] = "UPDATEAVATAR";
    AVATAR["audience"] = audiencename;
    AVATAR["avatar"] = filename;
    AVATAR.toStyledString();

    std::string message = AVATAR.toStyledString();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);

    std::string m;

    m = sock.receive();
    if(m == "HASCHANGED"){
        QString source = QString::fromStdString(filename);
        emit updateAvatarSucceed(source);
    }else if(m == "FAILED"){
        emit updateAvatarFailed();
    }
}

std::string Client::getAudienceAvatar(std::string name)
{
    Json::Value AudienceInfo;
    AudienceInfo["request"] = "GETAVATAR";
    AudienceInfo["name"] = name;
    AudienceInfo.toStyledString();
    std::string message = AudienceInfo.toStyledString();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);

    NetWork sock(udpsockptr);

    std::string m;

    m = sock.receive();

    return m;
}
