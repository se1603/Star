//董梦丹 4-25
//最后修改于 5-17
#include "audience.h"

#include "audience.h"
#include "movieandtelevision.h"

Audience::Audience(std::string name, std::string password, std::string avatar, std::vector<Collection> collections, std::vector<Record> records, std::multimap<std::string, Comment> comments)
{
    m_name = name;
    m_password = password;
    m_avatar = avatar;
    m_collections = collections;
    m_records = records;
    m_comments = comments;
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

void Audience::addCollection(Collection c)
{
    m_collections.push_back(c);
}

void Audience::addRecord(Record r)
{
    m_records.push_back(r);
}

void Audience::showCollection(std::map<std::string, MovieAndTelevision *> &collectionmap)
{
    for(auto c:m_collections){
        collectionmap.insert(std::make_pair(c.m_collectionTime,c.m_movieAndTelevision));
    }
}

void Audience::showRecord(std::map<std::string, MovieAndTelevision *> &recordmap)
{
    for(auto r:m_records){
        std::string m = r.m_startPlayTime+"/"+r.m_duration;
        recordmap.insert(std::make_pair(m,r.m_movieAndTelevision));
    }
}
