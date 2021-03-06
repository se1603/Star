//董梦丹 4-21
//最后修改于 4-28
#ifndef AUDIENCE_H
#define AUDIENCE_H
#include <QObject>
#include <iostream>
#include <string>
#include <vector>
#include "collection.h"
#include "record.h"

class Collection;
class Record;
class Client;
class Audience
{
    friend class Client;
public:
    Audience();
private:
    QString m_name;
    QString m_password;
    QString m_avatar;

    std::vector<Collection> m_collections;
    std::vector<Record> m_records;
};

#endif // AUDIENCE_H
