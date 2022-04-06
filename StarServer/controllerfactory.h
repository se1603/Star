#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include "browseandwatchcontroller.h"
#include "audiencecontroller.h"
#include "commentcontroller.h"
#include "searchcontroller.h"

class ControllerFactory
{
public:
    static ControllerFactory* getInstance(){
        return m_instance;
    }

    ~ControllerFactory();

    BrowseAndWatchController* createBrowseAndWatchController();

    AudienceController *createAudienceController();
    CommentController *createCommentController();
    SearchController *creatSearchController();

private:
    ControllerFactory();
    static ControllerFactory* m_instance;
};

#endif // CONTROLLERFACTORY_H
