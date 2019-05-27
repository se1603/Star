#include "controllerfactory.h"

ControllerFactory* ControllerFactory::m_instance = new ControllerFactory();

ControllerFactory::ControllerFactory()
{

}

ControllerFactory::~ControllerFactory()
{
    delete m_instance;
}

BrowseAndWatchController *ControllerFactory::createBrowseAndWatchController()
{
    return BrowseAndWatchController::getInstance();
}

AudienceController* ControllerFactory::createAudienceController()
{
    return AudienceController::getInstance();
}

CommentController *ControllerFactory::createCommentController()
{
    return CommentController::getInstance();
}
