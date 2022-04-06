#ifndef SEARCHCONTROLLER_H
#define SEARCHCONTROLLER_H
#include <iostream>
#include "controller.h"
#include "movieandtelevisionbroker.h"
#include "actorbroker.h"
#include "directorbroker.h"
#include "browseandwatchcontroller.h"

class SearchController: public Controller
{
public:
    static SearchController* getInstace()
    {
        return m_instance;
    }

    ~SearchController();
    std::string searchKeywords(std::string name); //搜索关键字

private:
    SearchController();
    static SearchController* m_instance;
    ActorBroker* m_actorbroker;
    DirectorBroker* m_directorbroker;
    MovieAndTelevisionBroker* m_movieAndTelevisionBroker;
    BrowseAndWatchController* m_browseAndWatchController;
};

#endif // SEARCHCONTROLLER_H
