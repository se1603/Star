#ifndef COMMENTBROKER_H
#define COMMENTBROKER_H


//内容：评论的代管者
//时间：2019.5.20
//author：徐丹
#include <map>
#include "comment.h"
#include "relationalbroker.h"

class AudienceBroker;
class MovieAndTelevisionBroker;
class MovieAndTelevision;
class Audience;

class CommentBroker: public RelationalBroker
{
public:
    static CommentBroker* getInstance()
    {
        return m_instance;
    }

    void infoFromDataBase(std::vector<std::string> &v);//获取数据库内容

    bool insertComment(std::string an, std::string mn, std::string t,std::string c);//把数据存入数据库

    void initcomment(std::string n, std::string c, std::string t, Audience* a, MovieAndTelevision *m);//初始化评论
    bool CommentSize();

    void getCommentInfo(std::string name, std::vector<std::string> &v);//获取所有评论
    void goodCommentInfo(std::string name,std::vector<std::string> &v);//获取精华评论
private:
    CommentBroker();
    static CommentBroker* m_instance;
    std::multimap<std::string,Comment> m_comments;//一键对多值
};
#endif // COMMENTBROKER_H
