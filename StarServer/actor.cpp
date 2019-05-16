#include "actor.h"

Actor::Actor(std::vector<std::string> paramters, Region region)
{
    m_name = paramters[0];
    m_birthday = paramters[1];
    m_introduction = paramters[2];
    m_photo = paramters[3];
    m_region = region;
}

Actor::Actor(std::string name)
{
    m_name = name;
    m_birthday = "未知";
    m_introduction = "未知";
    m_photo = "未知";
}

Actor::Actor()
{
    m_name = " ";
    m_birthday = " ";
    m_introduction = " ";
    m_photo = "./images/actors/default.png";
}

void Actor::addMovieAndTelevision(MovieAndTelevision *movieAndTelevision)
{
    m_movieAndTelevision.push_back(movieAndTelevision);
}
