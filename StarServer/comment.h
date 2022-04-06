#ifndef COMMENT_H
#define COMMENT_H


#include <vector>
#include <iostream>

class Audience;
class MovieAndTelevision;

class Comment
{
public:
    Comment(std::string time,std::string comment,Audience* a,MovieAndTelevision* m);
    Comment(std::string time,std::string comment);

    void getCommentInfo(std::vector<std::string> &v);//获得评论内容
    bool commentSize();

private:
    std::string m_time;
    std::string m_comment;
//    std::string m_aName;

    Audience* m_audience;
    MovieAndTelevision* m_movieAndTelevision;
};

#endif // COMMENT_H
