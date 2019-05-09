//董梦丹 4-25
//最后修改于 4-25
#include "audience.h"

Audience::Audience(std::string name, std::string password, std::string avatar)
{
    m_name = name;
    m_password = password;
    m_avatar = avatar;
}

bool Audience::judgeLogin(std::string name)
{
    if(name == m_name)
        return true;
    else
        return false;
}

bool Audience::judgeName(std::string name)
{

}

bool Audience::judgePassword(std::string password)
{

}
