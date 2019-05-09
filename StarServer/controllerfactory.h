#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include "browseandwatchcontroller.h"
#include "audiencecontroller.h"

class ControllerFactory
{
public:
    static std::shared_ptr<ControllerFactory> getInstance(){
        return m_instance;
    }

    std::shared_ptr<BrowseAndWatchController> createBrowseAndWatchController();

private:
    ControllerFactory();
    static std::shared_ptr<ControllerFactory> m_instance;
};

#endif // CONTROLLERFACTORY_H
