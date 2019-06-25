//董梦丹 5-08
//最后修改于5-17
#ifndef AUDIENCECONTROLLER_H
#define AUDIENCECONTROLLER_H

#include "controller.h"
#include "audiencebroker.h"
#include "movieandtelevisionbroker.h"

class AudienceController : public Controller
{
public:
    static AudienceController* getInstance()
    {
        return m_instance;
    }

    ~AudienceController();

    //判断用户信息的函数
    //登录，验证信息并生成用户收藏、记录的实体
    bool verifyAudience(std::string name, std::string password);
    //注册用户
    bool registeAudience(std::string name,std::string password);
    //添加用户到数据库
    bool insertAudience(std::string name,std::string password);
    //退出登录
    bool logoutAudience(std::string name);
    //判断用户是否已经登录
    bool checkoutAudience(std::string name);
    //更新用户头像
    bool updateAudienceAvatar(std::string name,std::string avatar);
    //添加用户收藏
    bool addAudienceCollection(std::string audiencename, std::string collectname,
                               std::string collecttime, std::string collecttype);
    //更新用户浏览历史
    bool updateAudienceRecord(std::string audiencename, std::string recordname,
                              std::string startPlayTime, std::string duration, std::string type);

    //处理用户信息的函数
    std::string audienceInfo(std::string name);
    void audienceCollection(std::string name, std::vector<std::string> &collectlist);
    void audienceRecord(std::string name, std::vector<std::string> &recordlist);
    std::string pakageCollection(std::vector<std::string> a_collections);
    std::string pakageRecord(std::vector<std::string> a_records);

    //处理字符串函数
    void splictString(std::string &s, std::vector<std::string> &v, const std::string &c);
private:
    AudienceController();
    static AudienceController* m_instance;
    AudienceBroker* m_audienceBroker;
    MovieAndTelevisionBroker* m_movieAndTelevisionBroker;
};

#endif // AUDIENCECONTROLLER_H
