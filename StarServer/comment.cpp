#include "comment.h"
#include "audience.h"
#include <iostream>
Comment::Comment(std::string time, std::string comment, Audience *a, MovieAndTelevision *m)
{
    m_time = time;
    m_comment = comment;
    m_audience = a;
    m_movieAndTelevision = m;
}

//Comment::Comment(std::string time, std::string comment, std::string n, MovieAndTelevision *m)
//{
//    m_time = time;
//    m_comment = comment;
//    m_aName = n;
//    m_movieAndTelevision = m;
//}

Comment::Comment(std::string time, std::string comment)
{
    m_time = time;
    m_comment = comment;
}

void Comment::getCommentInfo(std::vector<std::string> &v)
{
    v.push_back(m_time);
    v.push_back(m_comment);
    m_audience->showname(v);

}

bool Comment::commentSize()
{
//    std::cout << m_comment << "comment size is"<< m_comment.size() << std::endl;
    if(m_comment.size() > 10){
        return true;
    }else{
        return false;
    }
}
