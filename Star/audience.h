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
class Audience : public QObject
{
    friend class Client;
    Q_OBJECT
public:
    Audience(QObject* parent=0);

    //获取
    QString getName();
    QString getPassword();
    //设置
    void setName(std::string name);
    void setPassword(std::string password);
private:
    QString m_name;
    QString m_password;
    QString m_avatar;
    QStringList m_collectionList;
    QStringList m_recordList;

    std::vector<Collection*> m_collections;
    std::vector<Record*> m_records;
};

#endif // AUDIENCE_H
