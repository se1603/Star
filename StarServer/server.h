#ifndef SERVER_H
#define SERVER_H

#include <boost/thread.hpp>
#include <string>
#include "threadpool.h"
#include "json/json.h"
#include <boost/filesystem.hpp>
#include "network.h"
#include "controllerfactory.h"

struct File_info{
    typedef unsigned long long Size_type;
    size_t filename_size;  //文件名的长度
    Size_type filesize;    //文件的大小
    File_info() : filename_size(0), filesize(0){}
};

class Server
{
public:
    Server();

    void acceptMessage();     //接收客户端消息
    void processMessage(std::string message, endpoint ep);  //处理消息
    std::vector<std::string> jsonParse(char message[]);   //解析JSON
    std::string processRequest(std::string request,std::vector<std::string> parameters,endpoint ep);   //处理请求
    void sendMessage(std::string message, endpoint ep);  //发送回复消息

    void sendFile(std::string filename,endpoint ep);

private:
    ThreadPool threadpool;  //线程池
    ControllerFactory* controlFactory;
    BrowseAndWatchController* m_BrowseAndWatchController;
    SearchController *m_searchController;

    //观众控制器
    AudienceController* m_AudienceController;
    CommentController* m_commentController;
};

#endif // SERVER_H
