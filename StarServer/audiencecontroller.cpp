//董梦丹 5-08
#include "audiencecontroller.h"
#include "json/json.h"

std::shared_ptr<AudienceController> AudienceController::m_instance =
        std::make_shared<AudienceController>(AudienceController());
bool AudienceController::verifyAudience(std::string name, std::string password)
{
    if(m_audienceBroker->verifyLoginInfo(name,password) == true)
        return true;
    else
        return false;
}

bool AudienceController::registeAudience(std::string name, std::string password)
{
    if(m_audienceBroker->registeAccount(name,password) == true)
        return true;
    else
        return false;
}

bool AudienceController::insertAudience(std::string name, std::string password)
{
    if(m_audienceBroker->insertNewAudience(name,password) == true)
        return true;
    else
        return false;
}

bool AudienceController::logoutAudience(std::string name)
{
    if(m_audienceBroker->logoutAccount(name) == true)
        return true;
    else
        return false;
}

bool AudienceController::checkoutAudience(std::string name)
{
    if(m_audienceBroker->checkLoginAudience(name) == true)
        return true;
    else
        return false;
}

bool AudienceController::updateAudienceAvatar(std::string name, std::string avatar)
{
    if(m_audienceBroker->changeAudienceAvatar(name,avatar) == true)
        return true;
    else
        return false;
}

std::string AudienceController::audienceInfo(std::string name)
{
    std::vector<std::string> audienceinfo;
    m_audienceBroker->showAudienceInfo(name,audienceinfo);

    Json::Value root;
    root["request"] = "GETINFO";
    root["name"] = audienceinfo[0];
    root["avatar"] = audienceinfo[1];

    std::string info = root.toStyledString();
    return info;
}

AudienceController::AudienceController()
{
    m_audienceBroker = AudienceBroker::getInstance();
}
