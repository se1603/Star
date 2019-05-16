#include "director.h"

Director::Director(std::vector<std::string> paramters, Region region)
{
    m_name = paramters[0];
    m_birthday = paramters[1];
    m_introduction = paramters[2];
    m_photo = paramters[3];
    m_region = region;
}

Director::Director(std::string name)
{
    m_name = name;
    m_birthday = "未知";
    m_introduction = "未知";
    m_photo = "未知";
}

Director::Director()
{
    m_name = " ";
    m_birthday = " ";
    m_introduction = " ";
    m_photo = "./images/directors/default.png";
}

void Director::addMovieAndTelevision(MovieAndTelevision *movieAndTelevision)
{
    m_movieAndTelevision.push_back(movieAndTelevision);
}
