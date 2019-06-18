//董梦丹 4-25
//最后修改于 6-18
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
    //自动添加新的历史记录
    bool updateAudienceRecord(std::string audiencename, std::string recordname,
                              std::string startPlayTime, std::string duration, std::string type);
    //修改数据库
    bool changeDatabaseRecord(std::string audiencename, std::string recordname,
                              std::string startPlayTime, std::string duration, std::string type);
    //判断该影视是否已经看过
    bool judgeAudienceRecord(std::string audiencename, std::string recordname);
    //修改已看过的记录信息
    void changeAudienceRecord(std::string audiencename, std::string recordname, std::string startPlayTime, std::string duration);
    //生成所有用户的指针
    void initAudience();
    //处理字符串函数
    void splictString(std::string &s, std::vector<std::string> &v, const std::string &c);
    //根据名字查找指针
    void findAudience(std::string name,Audience* a);
private:
    AudienceBroker();
    static AudienceBroker* m_instance;

    std::vector<Audience> loginedAudiences;
    std::map<std::string,Audience*> allaudiences;
};

#endif // AUDIENCEBROKER_H
