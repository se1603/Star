#ifndef COMMENTBROKER_H
#define COMMENTBROKER_H
#include <map>
#include "comment.h"
#include "relationalbroker.h"

class CommentBroker: public RelationalBroker
{
public:
    static CommentBroker* getInstance()
    {
        return m_instance;
    }
    void initComment();
private:
    CommentBroker();
    static CommentBroker* m_instance;
    std::multimap<std::string,Comment> m_comments;
};

#endif // COMMENTBROKER_H
