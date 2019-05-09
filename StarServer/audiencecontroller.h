#ifndef AUDIENCECONTROLLER_H
#define AUDIENCECONTROLLER_H
#include "controller.h"
#include "audiencebroker.h"

class AudienceController : public Controller
{
public:
    static std::shared_ptr<AudienceController> getInstance()
    {
        return m_instance;
    }
private:
    AudienceController();
    static std::shared_ptr<AudienceController> m_instance;
    std::shared_ptr<AudienceBroker> m_audiencebroker;
};

#endif // AUDIENCECONTROLLER_H
