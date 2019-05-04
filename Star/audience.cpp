#include "audience.h"

Audience::Audience(QObject* parent):QObject(parent)
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

void Audience::setName(std::string name)
{
    m_name = QString::fromStdString(name);
}

void Audience::setPassword(std::string password)
{
    m_password = QString::fromStdString(password);
}
