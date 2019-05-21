#ifndef COMMENT_H
#define COMMENT_H
#include <iostream>

class Audience;
class MovieAndTelevision;

class Comment
{
public:
    Comment(std::string time,std::string comment,Audience* a,MovieAndTelevision* m);
    Comment(std::string time,std::string comment);

private:
    std::string m_time;
    std::string m_comment;

    Audience* m_audience;
    MovieAndTelevision* m_movieAndTelevision;
};

#endif // COMMENT_H
