//董梦丹 5-08
#ifndef AUDIENCECONTROLLER_H
#define AUDIENCECONTROLLER_H

#include "controller.h"
#include "audiencebroker.h"

class AudienceController : public Controller
{
public:
    static AudienceController* getInstance()
    {
        return m_instance;
    }

    ~AudienceController();

    bool verifyAudience(std::string name,std::string password);
    bool registeAudience(std::string name,std::string password);
    bool insertAudience(std::string name,std::string password);
    bool logoutAudience(std::string name);
    bool checkoutAudience(std::string name);
    bool updateAudienceAvatar(std::string name,std::string avatar);

    std::string audienceInfo(std::string name);
private:
    AudienceController();
    static AudienceController* m_instance;
    AudienceBroker* m_audienceBroker;
};

#endif // AUDIENCECONTROLLER_H
