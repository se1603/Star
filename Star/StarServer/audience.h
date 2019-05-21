//董梦丹 4-25
//最后修改于 5-17
#ifndef AUDIENCE_H
#define AUDIENCE_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "collection.h"
#include "record.h"
#include "comment.h"

class Audience
{
public:
    Audience(std::string name,std::string password,std::string avatar,
             std::vector<Collection> collections,
             std::vector<Record> records,std::multimap<std::string,Comment> comments);

    bool verifyLogin(std::string name);
    bool verifyName(std::string name);
    bool verifyPassword(std::string password);

    void show(std::vector<std::string> &audienceinfo);
    void addCollection(Collection c);
    void addRecord(Record r);
    void showCollection(std::map<std::string,MovieAndTelevision*> &collectionmap);
    void showRecord(std::map<std::string,MovieAndTelevision*> &recordmap);
private:
    std::string m_name;
    std::string m_password;
    std::string m_avatar;

    std::multimap<std::string,Comment> m_comments;
    std::vector<Record> m_records;
    std::vector<Collection> m_collections;
};
#endif // AUDIENCE_H
