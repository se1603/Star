//董梦丹 4-25
//最后修改于 5-17
#ifndef AUDIENCEBROKER_H
#define AUDIENCEBROKER_H
#include "relationalbroker.h"
#include "audience.h"

class Audience;
class Collection;
class MovieAndTelevision;
class Record;
class AudienceBroker : public RelationalBroker
{
public:
    static AudienceBroker* getInstance()
    {
        return m_instance;
    }

    ~AudienceBroker();
    //验证登录信息
    bool verifyLoginInfo(std::string n,std::string p, std::vector<std::string> &audienceInfo);
    //注册新帐号
    bool registeAccount(std::string n,std::string p);
    //添加新用户到数据库中
    bool insertNewAudience(std::string n,std::string p);
    //退出登录
    bool logoutAccount(std::string n);
    //检查帐号是否已经登录
    bool checkLoginAudience(std::string n);
    //更改某帐号头像
    bool changeAudienceAvatar(std::string name,std::string source);
    //显示用户信息
    void showAudienceInfo(std::string name, std::vector<std::string> &audienceinfo);
    //生成用户收藏
    void createAudienceCollection(std::string aname, std::string collecttime, MovieAndTelevision* m);
    //生成用户记录
    void createAudienceRecord(std::string aname, std::string startPlayTime, std::string duration,
                              MovieAndTelevision *m);
    //读取用户记录
    void readAudienceRecord(std::string name, std::map<std::string,MovieAndTelevision*> &recordmap);
    //读取用户收藏
    void readAudienceCollection(std::string name, std::map<std::string,MovieAndTelevision*> &collectionmap);
    //添加用户收藏
    bool addAudienceCollection(std::string aName, std::string cName, std::string cTime, std::string cType);
    //处理字符串函数
    void splictString(std::string &s, std::vector<std::string> &v, const std::string &c);
private:
    AudienceBroker();
    static AudienceBroker* m_instance;

    std::vector<Audience> loginedAudiences;
};

#endif // AUDIENCEBROKER_H
