/* Author:王梦娟
 * Date:2019-4-25
 * Note:控制器工厂
*/
#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include "browseandwatchcontroller.h"
#include "audiencecontroller.h"

class ControllerFactory
{
public:
    static ControllerFactory* getInstance(){
        return m_instance;
    }

    ~ControllerFactory();

    BrowseAndWatchController* createBrowseAndWatchController();

    AudienceController *createAudienceController();

private:
    ControllerFactory();
    static ControllerFactory* m_instance;
};

#endif // CONTROLLERFACTORY_H
