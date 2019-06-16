#include "comment.h"

Comment::Comment(std::string time, std::string comment, Audience *a, MovieAndTelevision *m)
{
    m_time = time;
    m_comment = comment;
    m_audience = a;
    m_movieAndTelevision = m;
}

Comment::Comment(std::string time, std::string comment)
{
    m_time = time;
    m_comment = comment;
}




