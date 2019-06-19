//董梦丹 4-25
//最后修改于 6-18
#ifndef AUDIENCE_H
#define AUDIENCE_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "collection.h"
#include "record.h"

class Audience
{
public:
    Audience(std::string name,std::string password,std::string avatar,
             std::vector<Collection> collections,
             std::vector<Record> records);
    Audience(std::string name);
    Audience();

    bool verifyLogin(std::string name);
    bool verifyName(std::string name);
    bool verifyPassword(std::string password);

    void show(std::vector<std::string> &audienceinfo);
    void addCollection(Collection c);
    void addRecord(Record r);
    void showCollection(std::map<std::string,MovieAndTelevision*> &collectionmap);
    void showRecord(std::map<std::string,MovieAndTelevision*> &recordmap);
    void showname(std::vector<std::string> &a);//获取用户名字

    bool judgeRecord(std::string recordname);
    void changeRecord(std::string recordname, std::string startPlayTime,
                      std::string duration);
private:
    std::string m_name;
    std::string m_password;
    std::string m_avatar;

    std::vector<Collection> m_collections;
    std::vector<Record> m_records;
};
#endif // AUDIENCE_H
