#include "movieandtelevision.h"

MovieAndTelevision::MovieAndTelevision()
{

}

bool MovieAndTelevision::isSame(std::string n)
{
    if(m_name == n)
        return true;
    else
        return false;
}

void MovieAndTelevision::showInfo(std::vector<std::string> &a_collections)
{
    a_collections.push_back(m_name);
    a_collections.push_back(m_post[0]);
}

void MovieAndTelevision::searchInfo(std::vector<std::string> &vec)
{
    vec.push_back(m_name);
    vec.push_back(m_post[0]);
    vec.push_back(m_introduction);
    vec.push_back(std::to_string(m_episode));
}
