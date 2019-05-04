//董梦丹 4-25
//最后修改于 4-25
#include "audience.h"

Audience::Audience()
{

}

std::string Audience::getName()
{
    return m_name;
}

std::string Audience::getPassword()
{
    return m_password;
}

std::string Audience::getAvatar()
{
    return m_avatar;
}

std::string Audience::getCollection()
{
    return m_collections;
}

std::string Audience::getRecord()
{
    return m_records;
}

void Audience::setName(std::string name)
{
    m_name = name;
}

void Audience::setPassword(std::string password)
{
    m_password = password;
}

void Audience::setAvatar(std::string avatar)
{
    m_avatar = avatar;
}

void Audience::setCollection(std::string collection)
{
    m_collections = collection;
}

void Audience::setRecord(std::string record)
{
    m_records = record;
}
