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
