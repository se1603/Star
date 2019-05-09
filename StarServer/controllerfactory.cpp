#include "controllerfactory.h"

std::shared_ptr<ControllerFactory> ControllerFactory::m_instance = std::make_shared<ControllerFactory>(ControllerFactory());

ControllerFactory::ControllerFactory()
{

}

std::shared_ptr<BrowseAndWatchController> ControllerFactory::createBrowseAndWatchController()
{
    return BrowseAndWatchController::getInstance();
}
