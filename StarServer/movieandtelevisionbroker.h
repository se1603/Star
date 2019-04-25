#ifndef MOVIEANDTELEVISIONBROKER_H
#define MOVIEANDTELEVISIONBROKER_H

#include "relationalbroker.h"

class MovieAndTelevisionBroker : public RelationalBroker
{
public:
    static std::shared_ptr<MovieAndTelevisionBroker> getInstance()
    {
        return m_instance;
    }


private:
    MovieAndTelevisionBroker();
    static std::shared_ptr<MovieAndTelevisionBroker> m_instance;
};

#endif // MOVIEANDTELEVISIONBROKER_H
