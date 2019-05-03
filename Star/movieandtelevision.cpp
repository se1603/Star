#include "movieandtelevision.h"

MovieAndTelevision::MovieAndTelevision()
{

}

std::string MovieAndTelevision::name() const
{
    return m_name;
}

void MovieAndTelevision::setName(const std::string &name)
{
    m_name = name;
}


std::string MovieAndTelevision::introduction() const
{
    return m_introduction;
}

void MovieAndTelevision::setIntroduction(const std::string &introduction)
{
    m_introduction = introduction;
}

Region MovieAndTelevision::region() const
{
    return m_region;
}

void MovieAndTelevision::setRegion(int regiontype)
{
    switch (regiontype) {
    case 1:
        m_region = Region::China;
        break;
    case 2:
        m_region = Region::American;
        break;
    case 3:
        m_region = Region::Korea;
        break;
    case 4:
        m_region = Region::India;
        break;
    case 5:
        m_region = Region::THailand;
        break;
    case 6:
        m_region = Region::Britain;
        break;
    default:
        break;
    }
}

std::vector<std::string> MovieAndTelevision::actors() const
{
    return m_actors;
}

void MovieAndTelevision::setActors(const std::vector<std::string> &actors)
{
    m_actors = actors;
}

std::vector<std::string> MovieAndTelevision::director() const
{
    return m_director;
}

void MovieAndTelevision::setDirector(const std::vector<std::string> &director)
{
    m_director = director;
}

int MovieAndTelevision::getRecommend() const
{
    return recommend;
}

void MovieAndTelevision::setRecommend(int value)
{
    recommend = value;
}

std::string MovieAndTelevision::post() const
{
    return m_post;
}

void MovieAndTelevision::setPost(const std::string &post)
{
    m_post = post;
}
