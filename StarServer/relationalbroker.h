#ifndef RELATIONALBROKER_H
#define RELATIONALBROKER_H

#include <mysql/mysql.h>
#include <memory>
#include <vector>
#include <map>
#include <iostream>

class RelationalBroker
{
public:
    RelationalBroker();

private:
    MYSQL m_database;
};

#endif // RELATIONALBROKER_H
