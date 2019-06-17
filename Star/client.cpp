/*Author:王梦娟
 *Date:2019-10-14
 *Note:缓存客户端发送过来的消息
*/
#include "client.h"
#include <iostream>
#include <qdebug.h>
#include "film.h"
#include <dirent.h>
#include <thread>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint serverep(boost::asio::ip::address::from_string("10.253.133.196"),8001);
boost::asio::ip::udp::socket udpsock(service,boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),7789));


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
    std::thread t(std::bind(&Client::getFile,this));
    t.detach();
}

void Client::getFile()
{
    std::string pathStart = "./";

    std::vector<std::string> pathNames{"recommend","films","comics","drama","varietyshow","actors","directors"};

    std::string pathEnd = ".tar.gz";

    for(int i = 0; i != pathNames.size();i++)
    {
        std::string path = pathStart + pathNames[i];
        DIR * dir;
        dir = opendir(path.data());
        if(dir == nullptr )
        {
            Json::Value root;
            root["request"] = "FILETRANSFER";
            root["fileName"] =
                    pathNames[i] + pathEnd;
            root.toStyledString();
            std::string message = root.toStyledString();

            receiveFile(message);

            std::string commend = "tar xzvf " + pathNames[i] + pathEnd;
            system(commend.c_str());
        }
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

    std::string result;

    bool sendRequest = true;
    //先在缓存中找
    if(interfaceBuffer.find(category) != interfaceBuffer.end())
    {
        std::map<int,std::string> m1 = interfaceBuffer[category];
        if(m1.find(type) != m1.end())
        {
            sendRequest = false;
            std::string resoure = m1[type];
            result = resoure;
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

            qmlvalue = value["movieAndTelevision"];
            result = qmlvalue.toStyledString();

            int interface = value["interface"].asInt();
            int type = value["type"].asInt();

            if(interfaceBuffer.find(interface) == interfaceBuffer.end())
            {
                std::map<int,std::string> showresouce;
                showresouce[type] = result;
                interfaceBuffer[category] = showresouce;
            }
            else
            {
                std::map<int,std::string> showresouce;
                showresouce = interfaceBuffer[interface];
                if(showresouce.find(type) == showresouce.end())
                {
                    showresouce[type] == result;
                }
            }
        }
    }

    //    std::cout << qmlvalue.toStyledString() << std::endl;
    QString t = QString::fromStdString(result);
    return t;
}

QString Client::showCategory(int type)
{
    Json::Value qmlvalue;
    std::string result;
    bool sendRequest = true;

    //先在缓存中找
    if(categoryBuffer.find(type) != categoryBuffer.end())
    {
        sendRequest = false;
        std::string resoure = categoryBuffer[type];
        result = resoure;
    }

    if(sendRequest)
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

        Json::Reader reader;
        std::string res = sock.receive();

        if(!reader.parse(res,value))
        {
            std::cerr << "Receive message failed." << std::endl;
        }
        else
        {
            qmlvalue = value["categorys"];
            result = qmlvalue.toStyledString();

            if(categoryBuffer.find(type) == categoryBuffer.end())
            {

                categoryBuffer[type] = result;
            }
        }
    }
    //    std::cout << qmlvalue.toStyledString() << std::endl;

    QString t = QString::fromStdString(result);
    return t;
}

QString Client::showRecommend(int category)
{
    Json::Value qmlvalue;
    std::string result;
    bool sendRequest = true;

    //先在缓存中找
    if(recommendBuffer.find(category) != recommendBuffer.end())
    {
        sendRequest = false;
        std::string resoure = recommendBuffer[category];
        result = resoure;
    }

    if(sendRequest)
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

        Json::Reader reader;
        if(!reader.parse(res,value))
        {
            std::cerr << "Receive message failed." << std::endl;
        }
        else
        {
            qmlvalue["resource"] = value["resource"];
            qmlvalue["firstRecommends"] = value["firstRecommends"];
            qmlvalue["secondRecommends"] = value["secondRecommends"];

            result = qmlvalue.toStyledString();

            if(recommendBuffer.find(category) == recommendBuffer.end())
            {
                recommendBuffer[category] = result;
            }
        }
    }

    //    std::cout << qmlvalue.toStyledString() << std::endl;
    QString t = QString::fromStdString(result);
    return t;
}

QString Client::getMovieInfo(QString n)
{
    Json::Value recode;
    recode["request"] = "MOVIEINFO";
    recode["name"] = n.toStdString();
    recode.toStyledString();
    std::string message = recode.toStyledString();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);

    std::string receive;
    receive = sock.receive();

    Json::Value value;
    Json::Value qmlvalue;
    Json::Reader reader;
    if(!reader.parse(receive,value))
    {
        std::cerr << "Receive message failed." << std::endl;
    }
    else {
        qmlvalue["resource"] = value["resource"];
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
    std::string message = audience.toStyledString();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);


    NetWork sock(udpsockptr);
    std::string m;

    m = sock.receive();
    if(m == "LOGINSUCCEED"){
        getAudienceInfo(aN);
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
    //    std::cout << audiencename << filename << std::endl;

    Json::Value AVATAR;
    AVATAR["request"] = "UPDATEAVATAR";
    AVATAR["audience"] = audiencename;
    AVATAR["avatar"] = filename;

    std::string message = AVATAR.toStyledString();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);

    std::string m;

    m = sock.receive();
    if(m == "HASCHANGED"){
        emit updateAvatarSucceed(QString::fromStdString(filename));
    }else if(m == "FAILED"){
        emit updateAvatarFailed();
    }
}

QString Client::audienceCollection(QString name)
{
    auto aN = name.toStdString();
    Json::Value root;
    root["request"] = "GETCOLLECTION";
    root["name"] = aN;
    std::string message = root.toStyledString();

    socket_ptr udpsock;
    udpsock = sendMessage(message);
    NetWork sock(udpsock);
    std::string res = sock.receive();

    Json::Value value;
    Json::Value qmlvalue;
    Json::Reader reader;

    if(!reader.parse(res,value)){
        std::cerr << "Receive collection message failed." << std::endl;
    }else{
        qmlvalue = value["collections"];
    }

    QString c = QString::fromStdString(qmlvalue.toStyledString());
    return c;
}

QString Client::audienceRecord(QString name)
{
    std::string aN = name.toStdString();
    Json::Value root;
    root["request"] = "GETRECORD";
    root["name"] = aN;
    root.toStyledString();
    std::string message = root.toStyledString();

    socket_ptr udpsock;
    udpsock = sendMessage(message);
    NetWork sock(udpsock);
    std::string res = sock.receive();

    Json::Value value;
    Json::Value qmlvalue;
    Json::Reader reader;
    if(!reader.parse(res,value)){
        std::cerr << "Receive record message failed." << std::endl;
    }else{
        qmlvalue = value["records"];
    }

    QString r = QString::fromStdString(qmlvalue.toStyledString());
    return r;
}

void Client::addCollection(QString name, QString collecttime, QString videoname, QString type)
{
    Json::Value root;
    std::cout << name.toStdString() <<":" << collecttime.toStdString()
              << ":" << videoname.toStdString() << ":" << type.toStdString() << std::endl;
    root["request"] = "ADDCOLLECTION";
    root["audiencename"] = name.toStdString();
    root["collecttime"] = collecttime.toStdString();
    root["collectname"] = videoname.toStdString();
    root["collecttype"] = type.toStdString();
    root.toStyledString();
    std::string message = root.toStyledString();

    socket_ptr udpsock;
    udpsock = sendMessage(message);
    NetWork sock(udpsock);

    std::string res = sock.receive();
    if(res == "COLLECTSUCCEED"){
        emit collectsucceed();
    }else if(res == "COLLECTFAILED"){
        emit collectfailed();
    }
}

void Client::addRecord(QString name, QString recordname, QString startPlaytime, QString duration, QString type)
{
    Json::Value root;
    root["request"] = "UPDATERECORD";
    root["audiencename"] = name.toStdString();
    root["recordname"] = recordname.toStdString();
    root["startPlayTime"] = startPlaytime.toStdString();
    root["duration"] = duration.toStdString();
    root["type"] = type.toStdString();

    std::string message = root.toStyledString();

    socket_ptr udpsock;
    udpsock = sendMessage(message);
    NetWork sock(udpsock);

    std::string res = sock.receive();
    if(res == "SUCCEED"){
        recordupdatesucceed();
    }else{
        recordupdatefailed();
    }
}

void Client::getAudienceInfo(std::string name)
{
    Json::Value AudienceInfo;
    AudienceInfo["request"] = "GETAUDIENCEINFO";
    AudienceInfo["name"] = name;
    AudienceInfo.toStyledString();
    std::string message = AudienceInfo.toStyledString();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);

    NetWork sock(udpsockptr);

    std::string m;
    m = sock.receive();

    Json::Value value;
    Json::Reader reader;

    std::vector<std::string> p;

    if(!reader.parse(m,value)){
        std::cerr << "Receive info failed." << std::endl;
    }else{
        p.push_back(value["name"].asString());
        p.push_back(value["avatar"].asString());
    }

    QString n = QString::fromStdString(p[0]);
    QString a = QString::fromStdString(p[1]);
    //    qDebug() << n << "------" << a;
    emit loginsucceed(n,a);

}

QString Client::showCommentInfo(QString name)
{
    Json::Value comment;
    comment["request"] = "SHOWCOMMENT";
    comment["name"] = name.toStdString();

    comment.toStyledString();
    std::string message = comment.toStyledString();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);

    std::string receive;
    receive = sock.receive();

    Json::Value root;
    Json::Value value;
    Json::Reader reader;
    if(!reader.parse(receive,value)){
        std::cerr << "Receive message failed." << std::endl;
    } else{
        root["resource"] = value["resource"];
    }
    std::cout << root.toStyledString() << std::endl;
    QString t = QString::fromStdString(root.toStyledString());
    return t;
}

QString Client::showGoodComment(QString name)
{
    Json::Value comment;
    comment["request"] = "SHOWGOODCOMMENT";
    comment["name"] = name.toStdString();

    comment.toStyledString();
    std::string message = comment.toStyledString();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);

    std::string receive;
    receive = sock.receive();

    Json::Value root;
    Json::Value value;
    Json::Reader reader;
    if(!reader.parse(receive,value)){
        std::cerr << "Receive message failed." << std::endl;
    } else{
        root["resource"] = value["resource"];
    }
    std::cout << root.toStyledString() << std::endl;
    QString t = QString::fromStdString(root.toStyledString());
    return t;
}

void Client::addComment(QString aName, QString videoname, QString t, QString c)
{
    Json::Value root;
    std::cout << aName.toStdString() <<":" << t.toStdString()
              << ":" << videoname.toStdString() << ":" << c.toStdString() << std::endl;
    root["request"] = "INSERTCOMMENT";
    root["audiencename"] = aName.toStdString();
    root["name"] = videoname.toStdString();
    root["time"] = t.toStdString();
    root["comment"] = c.toStdString();
    root.toStyledString();
    std::string message = root.toStyledString();

    socket_ptr udpsock;
    udpsock = sendMessage(message);
    NetWork sock(udpsock);

    std::string res = sock.receive();
    if(res == "FAILED"){
        emit insertFailed();
    }else{
        emit insertSuccessed();
    }
}
QString Client::getActorInfo(QString n)
{
    Json::Value infomation;
    infomation["request"] = "INFOMATION";
    infomation["name"] = n.toStdString();

    infomation.toStyledString();
    std::string message = infomation.toStyledString();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);

    std::string receive;
    receive = sock.receive();

    Json::Value root;
    Json::Value value;
    Json::Reader reader;

    if(!reader.parse(receive,value))
    {
        std::cerr << "Receive message failed." << std::endl;
    }
    else {
        root["resource"] = value["resource"];
    }
    std::cout << root.toStyledString() << std::endl;
    QString t = QString::fromStdString(root.toStyledString());
    return t;
}
