//内容：评论控制类
//时间：2019.5.22
//author：徐丹
#ifndef COMMENTCONTROLLER_H
#define COMMENTCONTROLLER_H


#include "controller.h"
#include "audiencebroker.h"
#include "movieandtelevisionbroker.h"
#include "commentbroker.h"

class CommentController: public Controller
{
public:
    static CommentController* getInstance(){
        return m_instance;
    }

    ~CommentController();

    std::string getCommentInfo(std::string name);//获取评论内容
    bool insertComment(std::string an,std::string mn,std::string t,std::string c);//数据存入数据库

    std::string goodCommentInfo(std::string name);//获取精华评论
private:
    CommentController();
//    static CommentController* m_instance;
    static CommentController* m_instance;
    AudienceBroker* m_audienceBroker;
    MovieAndTelevisionBroker* m_movieAndTelevisionBroker;
    CommentBroker* m_commentBroker;
};
#endif // COMMENTCONTROLLER_H
