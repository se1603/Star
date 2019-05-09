//董梦丹 4-25
//最后修改于 4-27
#ifndef AUDIENCEBROKER_H
#define AUDIENCEBROKER_H
#include "relationalbroker.h"
#include <string>
#include "audience.h"

class Audience;
class Collection;
class MovieAndTelevision;
class Record;
class AudienceBroker : public RelationalBroker
{
public:
    static std::shared_ptr<AudienceBroker> getInstance()
    {
        return m_instance;
    }

    //验证登录信息
    bool verifyLoginInfo(std::string n,std::string p);
    //注册新帐号
    bool registeAccount(std::string n,std::string p);
    //添加新用户到数据库中
    bool insertNewAudience(std::string n,std::string p);
    //退出登录
    bool logoutAudience(std::string n);
    //检查帐号是否已经登录
    bool checkLoginaudience(std::string n,std::string p);
    //获取某帐号头像
    std::string getAudienceAvatar(std::string n);
    //更改某帐号头像
    bool changeAudienceAvatar(std::string name,std::string source);
private:
    AudienceBroker();
    static std::shared_ptr<AudienceBroker> m_instance;

    std::vector<Audience> loginedAudiences;
};

#endif // AUDIENCEBROKER_H
