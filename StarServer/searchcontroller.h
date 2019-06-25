/*Author:古长蓉
 * date： 2019-06-20 搜索控制器，从浏览影视控制器中分离
 */
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
