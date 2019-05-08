/* Author:王梦娟
 * Date:2019-4-25
 * Note:控制器工厂
*/
#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include "browseandwatchcontroller.h"

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
