#ifndef ACTORBROKER_H
#define ACTORBROKER_H

#include "actor.h"
#include "relationalbroker.h"

class ActorBroker:public RelationalBroker
{
public:
    static ActorBroker* getInstance(){
        if(m_instance == nullptr)
            m_instance = new ActorBroker();
        return m_instance;
    }
    ~ActorBroker();
    std::map<std::string, Actor> returnActor();
    void initActors();
    Actor handleActor(std::vector<std::string> row);

    std::vector<Actor *> findActor(std::vector<std::string> actors);
    void addMovieAndTelevision(std::vector<std::string> actors, MovieAndTelevision &mat);

    std::vector<Actor *> searchActor(std::string name); //搜索演员

private:
    ActorBroker();
    static ActorBroker* m_instance;
    std::map<std::string,Actor> m_actors; //演员
};

#endif // ACTORBROKER_H
