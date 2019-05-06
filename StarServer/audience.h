//董梦丹 4-25
//最后修改于 4-25
#ifndef AUDIENCE_H
#define AUDIENCE_H
#include <iostream>
#include <string>
#include <vector>
#include "collection.h"
#include "record.h"

class Audience
{
public:
    Audience();

    //获取
    std::string getName();
    std::string getPassword();
    std::string getAvatar();
    std::string getCollection();
    std::string getRecord();
    //设置
    void setName(std::string name);
    void setPassword(std::string password);
    void setAvatar(std::string avatar);
    void setCollection(std::string collection);
    void setRecord(std::string record);
private:
    std::string m_name;
    std::string m_password;
    std::string m_avatar;

    std::string m_collections;
    std::string m_records;
};

#endif // AUDIENCE_H
