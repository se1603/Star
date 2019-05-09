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
    Audience(std::string name,std::string password,std::string avatar);
    bool judgeLogin(std::string name);
    bool judgeName(std::string name);
    bool judgePassword(std::string password);

private:
    std::string m_name;
    std::string m_password;
    std::string m_avatar;

    std::vector<Collection> m_collections;
    std::vector<Record> m_records;
};

#endif // AUDIENCE_H
