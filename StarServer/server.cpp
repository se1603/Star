/* Author:王梦娟
 * Date:2019-4-25
 * Note:用封装好的NetWork重写网络连接
 * author：古长蓉
 * data：2019-06-17 增加搜索标签
*/
#include "server.h"
#include <iostream>
#include <algorithm>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint udpep(boost::asio::ip::udp::v4(),8001);


Server::Server()
{
    controlFactory = ControllerFactory::getInstance();
    m_BrowseAndWatchController = controlFactory->createBrowseAndWatchController();
    m_AudienceController = controlFactory->createAudienceController();
    m_commentController = controlFactory->createCommentController();
}

void Server::acceptMessage()
{

    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,udpep));
    NetWork sock(udpsock);
    std::string message;

    boost::asio::ip::udp::endpoint sender_ep;
    //接收客户消息，接收到消息以后将处理任务添加到线程池任务队列
    while (1) {

        message = sock.receive(sender_ep);
        std::cout << "message:" << message << std::endl;

        threadpool.append(std::bind(&Server::processMessage, this,message,sender_ep));
    }
}

void Server::processMessage(std::string message,endpoint ep)
{
    std::cout << std::this_thread::get_id() << std::endl;
    std::cout << ep.address().to_string() + " send: " + message << std::endl;

    char data[512];
    memset(data,0,sizeof (char) * 512);
    strcpy(data,message.data());
    auto request = jsonParse(data);

    processRequest(request[0],request,ep);

    //    threadpool.append(std::bind(&Server::processRequest,this,request[0],request,ep));
}

std::vector<std::string> Server::jsonParse(char message[])
{
    std::vector<std::string> parameter;

    Json::Value value;
    Json::Reader reader;

    if(!reader.parse(message,value))
    {
        std::cerr << "Receive message failed." << std::endl;
    }
    else
    {
        std::string request = value["request"].asString();

        if(request == "FILETRANSFER")
        {
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["fileName"].asString());
        }
        else if(request == "INTERFACE")
        {
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["interface"].asString());
            parameter.push_back(value["type"].asString());
        }
        else if (request == "CATEGORY") {
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["type"].asString());
        }
        else if (request == "RECOMMEND") {
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["category"].asString());
        }
        else if(request == "VERIFYINFO")
        {
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["name"].asString());
            parameter.push_back(value["password"].asString());
        }
        else if(request == "REGISTEACCOUNT")
        {
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["name"].asString());
            parameter.push_back(value["password"].asString());
        }
        else if(request == "LOGOUT")
        {
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["name"].asString());
        }
        else if(request == "UPDATEAVATAR")
        {
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["audience"].asString());
            parameter.push_back(value["avatar"].asString());
        }
        else if(request == "GETAUDIENCEINFO")
        {
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["name"].asString());
        }
        else if(request == "GETCOLLECTION")
        {
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["name"].asString());
        }
        else if(request == "GETRECORD")
        {
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["name"].asString());
        }
        else if(request == "MOVIEINFO"){
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["name"].asString());
        }
        else if(request == "ADDCOLLECTION"){
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["audiencename"].asString());
            parameter.push_back(value["collectname"].asString());
            parameter.push_back(value["collecttime"].asString());
            parameter.push_back(value["collecttype"].asString());
        }
        else if(request == "UPDATERECORD"){
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["audiencename"].asString());
            parameter.push_back(value["recordname"].asString());
            parameter.push_back(value["startPlayTime"].asString());
            parameter.push_back(value["duration"].asString());
            parameter.push_back(value["type"].asString());
        }
        else if(request == "INFOMATION"){
            parameter.push_back(value["request"].asCString());
            parameter.push_back(value["name"].asCString());
        }
        else if(request == "SHOWCOMMENT"){
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["name"].asString());
        }
        else if(request == "SHOWGOODCOMMENT"){
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["name"].asString());
        }
        else if(request == "INSERTCOMMENT"){
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["audiencename"].asString());
            parameter.push_back(value["name"].asString());
            parameter.push_back(value["time"].asString());
            parameter.push_back(value["comment"].asString());
        }
        else if (request == "SEARCH") {
            parameter.push_back(value["request"].asString());
            parameter.push_back(value["name"].asString());
        }
        else
        {
            parameter.push_back("invalidMessage");
        }
    }
    return parameter;
}

std::string Server::processRequest(std::string request, std::vector<std::string> parameters, endpoint ep)
{
    std::cout << "Process Request: " << request << std::endl;

    std::string reply;

    if(request == "FILETRANSFER")
    {

        sendFile(parameters[1],ep);
        reply = "FILETRANSFERSUCCEED";
        char buff[sizeof (reply)];
        strcpy(buff,reply.data());
        sendMessage(buff,ep);
        return reply;
    }
    else if (request == "INTERFACE") {
        reply = m_BrowseAndWatchController->interface(
                    atoi(parameters[1].c_str()),atoi(parameters[2].c_str()));
        sendMessage(reply,ep);
        return reply;
    }
    else if(request == "CATEGORY"){
        reply = m_BrowseAndWatchController->category(atoi(parameters[1].c_str()));
        sendMessage(reply,ep);
        return reply;
    }
    else if (request == "RECOMMEND") {
        reply = m_BrowseAndWatchController->recommend(atoi(parameters[1].c_str()));
        sendMessage(reply,ep);
        return reply;
    }
    else if(request == "MOVIEINFO"){
        reply = m_BrowseAndWatchController->getVideoInfo(parameters[1]);
        sendMessage(reply,ep);
        return reply;
    }
    else if(request == "INFOMATION"){
        reply = m_BrowseAndWatchController->getActorInfo(parameters[1]);
        sendMessage(reply,ep);
        return reply;
    }
    else if(request == "VERIFYINFO")
    {
        if(m_AudienceController->checkoutAudience(parameters[1]) == true){
            if(m_AudienceController->verifyAudience(parameters[1],parameters[2]) == true)
            {
                reply = "LOGINSUCCEED";
                char buff[sizeof(reply)];
                strcpy(buff,reply.data());
                sendMessage(buff,ep);
                return reply;
            }
            else
            {
                reply = "VERIFYFAILED";
                char buff[sizeof(reply)];
                strcpy(buff,reply.data());
                sendMessage(buff,ep);
                return reply;
            }
        }
        else
        {
            reply = "HASLOGINED";
            char buff[sizeof(reply)];
            strcpy(buff,reply.data());
            sendMessage(buff,ep);
            return reply;
        }
    }
    else if(request == "REGISTEACCOUNT")
    {
        if(m_AudienceController->registeAudience(parameters[1],parameters[2]) == true)
        {
            reply = "REGISTESUCCEED";
            char buff[sizeof(reply)];
            strcpy(buff,reply.data());
            sendMessage(buff,ep);
            return reply;
        }
        else
        {
            reply = "REGISTEFAILED";
            char buff[sizeof(reply)];
            strcpy(buff,reply.data());
            sendMessage(buff,ep);
            return reply;
        }
    }
    else if(request == "LOGOUT")
    {
        if(m_AudienceController->logoutAudience(parameters[1]) == true)
        {
            reply = "LOGOUTSUCCEED";
            char buff[sizeof(reply)];
            strcpy(buff,reply.data());
            sendMessage(buff,ep);
            return reply;
        }
        else
        {
            reply = "LOGOUTFAILED";
            char buff[sizeof(reply)];
            strcpy(buff,reply.data());
            sendMessage(buff,ep);
            return reply;
        }
    }
    else if(request == "UPDATEAVATAR")
    {
        if(m_AudienceController->updateAudienceAvatar(parameters[1],parameters[2]) == true){
            reply = "HASCHANGED";
            char buff[sizeof(reply)];
            strcpy(buff,reply.data());
            sendMessage(buff,ep);
            return reply;
        }
        else
        {
            reply = "FAILED";
            char buff[sizeof(reply)];
            strcpy(buff,reply.data());
            sendMessage(buff,ep);
            return reply;
        }
    }
    else if(request == "GETAUDIENCEINFO")
    {
        reply = m_AudienceController->audienceInfo(parameters[1]);
        sendMessage(reply,ep);
        return reply;
    }
    else if(request == "GETCOLLECTION")
    {
        std::vector<std::string> collectlist;
        m_AudienceController->audienceCollection(parameters[1],collectlist);
        reply = m_AudienceController->pakageCollection(collectlist);
        sendMessage(reply,ep);
        return reply;
    }
    else if(request == "GETRECORD")
    {
        std::vector<std::string> recordlist;
        m_AudienceController->audienceRecord(parameters[1],recordlist);
        reply = m_AudienceController->pakageRecord(recordlist);
        sendMessage(reply,ep);
        return reply;
    }
    else if(request == "ADDCOLLECTION")
    {
        if(m_AudienceController->addAudienceCollection(parameters[1],parameters[2],parameters[3],
                                                       parameters[4]) == true)
        {
            reply = "COLLECTSUCCEED";
            sendMessage(reply,ep);
            return reply;
        }else{
            reply = "COLLECTFAILED";
            sendMessage(reply,ep);
            return reply;
        }
    }
    else if(request == "SHOWCOMMENT"){
        reply = m_commentController->getCommentInfo(parameters[1]);
        sendMessage(reply,ep);
        return reply;
    }
    else if(request == "SHOWGOODCOMMENT"){
        reply = m_commentController->goodCommentInfo(parameters[1]);
        sendMessage(reply,ep);
        return reply;
    }
    else if(request == "INSERTCOMMENT"){
        if(m_commentController->insertComment(parameters[1],parameters[2],parameters[3],
                                              parameters[4])==true){
            reply = "SUCESSED!";
            sendMessage(reply,ep);
            return reply;
        }else{
            reply = "FAILED";
            sendMessage(reply,ep);
            return reply;
        }
    }
    else if(request == "UPDATERECORD")
    {
        if(m_AudienceController->updateAudienceRecord(parameters[1],parameters[2],parameters[3],
                                                      parameters[4],parameters[5]) == true)
        {
            reply = "SUCCEED";
            sendMessage(reply,ep);
            return reply;
        }else{
            reply = "FAILED";
            sendMessage(reply,ep);
            return reply;
        }
    }
    else if(request == "SEARCH"){
        reply = m_BrowseAndWatchController->SearchKey(parameters[1]);  //[1]为传入的json对象的下标，第一个元素，request[0]，name[1]
        sendMessage(reply, ep);
        return reply;
    }
}

void Server::sendMessage(std::string message, endpoint ep)
{
    //    std::cout << "Send message:"  << message << std::endl;
    //创建一个新的套接字指向客户端。
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    boost::asio::ip::udp::endpoint sender_ep;

    NetWork sock(udpsock);

    sock.sendto(message,ep);

}

void Server::sendFile(std::string filename, endpoint ep)
{
    std::cout << "Send file:" << filename << std::endl;

    socket_ptr sock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    boost::asio::ip::udp::endpoint sender_ep;

    std::string path = "../StarServer/images/";
    path += filename;
    std::cout << path << std::endl;
    auto fileName = path.data();
    FILE *fp = fopen(fileName,"rb");

    boost::shared_ptr<FILE> file_ptr(fp,fclose); //退出后自动关闭文件

    //打开文件失败发送一个空的file_info到客户端
    if(fp == NULL){
        std::cout << "Cannot open file." << std::endl;
        File_info file_info;
        char buffer[16];
        memcpy(buffer, &file_info,sizeof (file_info));
        sock->send_to(boost::asio::buffer(buffer,sizeof(buffer)),ep);
        return;
    }

    clock_t costTime = clock();  //记录传送文件时长

    const size_t buffer_size = 512;
    char buffer[buffer_size];
    memset(buffer,0,sizeof (char) * buffer_size);
    File_info file_info;

    int filename_size = strlen(filename.data()) + 1;     //文件名
    size_t file_info_size = sizeof (file_info);
    size_t total_size = file_info_size + filename_size;
    if(total_size > buffer_size){
        std::cerr << "File name is too long";
        return;
    }

    file_info.filename_size = filename_size;

    fseek(fp,0,SEEK_END);     //设置文件指针到文件末尾
    file_info.filesize = ftell(fp);  //得到文件的大小
    rewind(fp);    //重新指向文件头

    std::cout << "filenamesize: " << filename_size << std::endl;
    std::cout << "filesize: " << file_info.filesize << std::endl;
    std::cout << "totalsize: " << total_size << std::endl;

    memcpy(buffer, &file_info, file_info_size);
    sock->send_to(boost::asio::buffer(buffer,file_info_size),ep);  //发送大小

    memcpy(buffer, filename.data(), filename_size);
    sock->send_to(boost::asio::buffer(buffer,filename_size),ep);  //发送文件名

    std::cout << "Send file: " << buffer << "\n";

    //发送文件内容
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    NetWork filesock(udpsock);

    long int total_bytes_read = 0;
    total_bytes_read = filesock.sendFile(fp,ep);

    //发送文件内容结束

    std::cout << "send totalsize: " << total_bytes_read << std::endl;
    costTime = clock() - costTime;
    if(costTime == 0) costTime = 1;

    double speed = total_bytes_read * (CLOCKS_PER_SEC / 1024.0 / 1024.0) / costTime;
    std::cout << "cost time: " << costTime / (double) CLOCKS_PER_SEC  << " s "
              << "  transferred_bytes: " << total_bytes_read << " bytes\n"
              << "speed: " <<  speed << " MB/s\n\n";
    return;
}
