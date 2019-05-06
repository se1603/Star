#include "client.h"
#include <iostream>
#include <qdebug.h>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint serverep(boost::asio::ip::address::from_string("10.253.103.248"),8001);
boost::asio::ip::udp::socket udpsock(service,boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),7789));
boost::asio::ip::udp::endpoint ep(boost::asio::ip::udp::v4(),6666);


Client::Client(QObject *parent):QObject(parent)
{
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
    //    getFile();
}

void Client::getFile()
{
    Json::Value root;
    root["request"] = "FILETRANSFER";
    root["fileName"] = "image.tar";
    root.toStyledString();
    std::string message = root.toStyledString();

    receiveFile(message);
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
        _audience->setName(aN);
        _audience->setPassword(aPW);
        _audience->setAvatar(getAudienceAvatar(aN));
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

QString Client::getMyName()
{
    return _audience->getName();
}

QString Client::getMyAvatar()
{
    return _audience->getAvatar();
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
        _audience->setAvatar(filename);
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
