#include "audience.h"

Audience::Audience()
{

}

QString Audience::getName()
{
    return m_name;
}

QString Audience::getPassword()
{
    return m_password;
}

QString Audience::getAvatar()
{
    return m_avatar;
}

void Audience::setName(std::string name)
{
    m_name = QString::fromStdString(name);
}

void Audience::setPassword(std::string password)
{
    m_password = QString::fromStdString(password);
}

void Audience::setAvatar(std::string source)
{
    m_avatar = QString::fromStdString(source);
}
