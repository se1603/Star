//董梦丹 4-25
//最后修改于 5-08
#include "audience.h"

Audience::Audience(std::string name, std::string password, std::string avatar, std::vector<Collection> collection, std::vector<Record> record)
{
    m_name = name;
    m_password = password;
    m_avatar = avatar;
    m_collections = collection;
    m_records = record;
}

bool Audience::verifyLogin(std::string name)
{
    if(m_name == name)
        return true;
    else
        return false;
}

bool Audience::verifyName(std::string name)
{
    if(m_name == name)
        return true;
    else
        return false;
}

bool Audience::verifyPassword(std::string password)
{
    if(m_password == password)
        return true;
    else
        return false;
}

void Audience::show(std::vector<std::string> &audienceinfo)
{
    audienceinfo.push_back(m_name);
    audienceinfo.push_back(m_avatar);
}
