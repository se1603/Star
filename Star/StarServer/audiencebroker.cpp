//董梦丹 4-25
//最后修改于 5-17
#include "audiencebroker.h"
#include "audience.h"
#include "collection.h"
#include "record.h"

AudienceBroker* AudienceBroker::m_instance = new AudienceBroker();

AudienceBroker::~AudienceBroker()
{
    delete m_instance;
}

bool AudienceBroker::verifyLoginInfo(std::string n, std::string p, std::vector<std::string> &audienceInfo)
{
    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0)){
        std::cout << "In getAudience:Connect MYSQL failed." << std::endl;
    }else{
        std::cout << "In getAudience:Connect MYSQL succeed." << std::endl;
    }


    std::string sql = "select * from audience where name = '"+n+"' and password = '"+p+"';";

    std::multimap<std::string,Comment> comment;

    if(mysql_query(mysql,sql.data())){
        std::cout << "查询失败(login)" << std::endl;
    }
    else
    {
        result = mysql_use_result(mysql);
        while(1)
        {
            row = mysql_fetch_row(result);
            if(row == nullptr){
                return false;
            }else{
                for(unsigned int i=0;i<mysql_num_fields(result);++i){
                    audienceInfo.push_back(std::string(row[i]));
                }
                std::vector<Collection> collection;
                std::vector<Record> record;

                Audience a(audienceInfo[0],audienceInfo[1],audienceInfo[2],collection,record,comment);
                loginedAudiences.push_back(a);
                return true;
            }
        }
    }
    if(mysql != nullptr)
        mysql_close(mysql);
}


bool AudienceBroker::registeAccount(std::string n, std::string p)
{
    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0)){
        std::cout << "In getAudience:Connect MYSQL failed." << std::endl;
    }else{
        std::cout << "In getAudience:Connect MYSQL succeed." << std::endl;
    }

    std::string sql = "select * from audience where name = '"+n+"'";

    if(mysql_query(mysql,sql.data())){
        std::cout << "查询失败(registe)" << std::endl;
    }
    else
    {
        std::cout << "查询成功(registe)" << std::endl;
        result = mysql_use_result(mysql);

        while(1)
        {
            row = mysql_fetch_row(result);
            if(row == nullptr){
                return insertNewAudience(n,p);
            }else{
                return false;
            }
        }
    }
    if(mysql != nullptr)
        mysql_close(mysql);
}

bool AudienceBroker::insertNewAudience(std::string n, std::string p)
{
    MYSQL *mysql;
    mysql = new MYSQL;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0)){
        std::cout << "In insertAudience:Connect MYSQL failed." << std::endl;
    }else{
        std::cout << "In insertAudience:Connect MYSQL succeed." << std::endl;
    }

    std::string sql = "insert into audience(name,password,avatar,collection,record) values('"+n+"','"+p+"','""','""','""');";

    if(mysql_query(mysql,sql.data())){
        std::cout << "Insert Failed" << std::endl;
        return false;
    }else{
        return true;
    }

    if(mysql != nullptr)
        mysql_close(mysql);

}

bool AudienceBroker::logoutAccount(std::string n)
{
    for(auto it = loginedAudiences.begin();it != loginedAudiences.end();){
        if((*it).verifyLogin(n) == true){
            it = loginedAudiences.erase(it);
            std::cout << "已退出" << std::endl;
            return true;
        }else{
            ++it;
        }
    }
}

bool AudienceBroker::checkLoginAudience(std::string n)
{
    int flag = 0;
    for(auto a:loginedAudiences){
        if(a.verifyName(n) == true){
            flag = 1;
            return false;
        }
    }
    if(flag == 0){
        return true;
    }
}

bool AudienceBroker::changeAudienceAvatar(std::string name, std::string source)
{
    MYSQL *mysql;
    mysql = new MYSQL;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0)){
        std::cout << "In changeAvatar:Connect MYSQL failed." << std::endl;
    }

    std::string sql = "update audience set avatar='"+source+"' where name = '"+name+"';";

    if(mysql_query(mysql,sql.data())){
        std::cout << "Update avatar failed" << std::endl;
        return false;
    }else{
        return true;
    }

    if(mysql != nullptr)
        mysql_close(mysql);
}

void AudienceBroker::showAudienceInfo(std::string name, std::vector<std::string> &audienceinfo)
{
    for(auto a:loginedAudiences){
        if(a.verifyName(name) == true){
            a.show(audienceinfo);
        }
    }
}

void AudienceBroker::createAudienceCollection(std::string aname, std::string collecttime, MovieAndTelevision *m)
{
    for(auto &la:loginedAudiences){
        if(la.verifyName(aname) == true){
            Collection c(collecttime,&la,m);
            la.addCollection(c);
        }
    }
}

void AudienceBroker::createAudienceRecord(std::string aname, std::string startPlayTime, std::string duration, MovieAndTelevision *m)
{
    for(auto &la:loginedAudiences){
        if(la.verifyName(aname) == true){
            Record r(startPlayTime,duration,&la,m);
            la.addRecord(r);
        }
    }
}

void AudienceBroker::readAudienceRecord(std::string name, std::map<std::string, MovieAndTelevision *> &recordmap)
{
    for(auto &la:loginedAudiences){
        if(la.verifyName(name) == true){
            la.showRecord(recordmap);
        }
    }
}

void AudienceBroker::readAudienceCollection(std::string name, std::map<std::string, MovieAndTelevision *> &collectionmap)
{
    for(auto &la:loginedAudiences){
        if(la.verifyName(name) == true){
            la.showCollection(collectionmap);
        }else{
            std::cout << "不存在" << std::endl;
        }
    }
}

bool AudienceBroker::addAudienceCollection(std::string aName, std::string cName, std::string cTime, std::string cType)
{
    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0)){
        std::cout << "In addCollection:Connect MYSQL failed." << std::endl;
    }else{
        std::cout << "In addCollection:Connect MYSQL succeed." << std::endl;
    }

    std::vector<std::string> audienceInfo;
    std::string sql = "select * from audience where name='"+aName+"';";
    std::cout << sql << std::endl;

    if(mysql_query(mysql,sql.data())){
        std::cout << "查询失败(collection)" << std::endl;
    }
    else
    {
        std::cout << "我进来了" << std::endl;
        result = mysql_use_result(mysql);
        while(1)
        {
            row = mysql_fetch_row(result);
            if(row == nullptr){
                break;
            }else{
                for(unsigned int i=0;i<mysql_num_fields(result);++i){
                    audienceInfo.push_back(std::string(row[i]));
                }

            }
        }
    }

    std::string collections = audienceInfo[3] + "/" + cName + " " + cTime + " " + cType;
    std::cout << collections << std::endl;

    std::string sql2 = "update audience set collection='"+collections+"' where name='"+aName+"';";
    if(mysql_query(mysql,sql2.data())){
        std::cout << "更新收藏失败" << std::endl;
        return false;
    }

    if(mysql != nullptr)
        mysql_close(mysql);

    std::cout << "更新收藏成功" << std::endl;
    return true;
}

void AudienceBroker::splictString(std::string &s, std::vector<std::string> &v, const std::string &c)
{
    std::string::size_type pos1,pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2){
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

void AudienceBroker::initComment()
{
    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0)){
        std::cout << "In getAudience:Connect MYSQL failed." << std::endl;
    }else{
        std::cout << "In getAudience:Connect MYSQL succeed." << std::endl;
    }
    std::string sql = "select * from Comment";
    if(mysql_query(mysql,sql.data())){
        std::cout << "Comment 获取失败"<< std::endl;
    }else{
        result = mysql_use_result(mysql);//获取结果集
        while(1){
            row = mysql_fetch_row(result);
            if(row == nullptr) break;
            std::vector<std::string> res;
            for(unsigned i = 0; i < mysql_num_fields(result);++i){
                res.push_back(row[i]);
                std::cout << i << " " << row[i] << std::endl;
            }
//            Comment c = Comment()
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr)
            mysql_close(mysql);
    mysql_library_end();
}

AudienceBroker::AudienceBroker()
{
//    initComment();
}
