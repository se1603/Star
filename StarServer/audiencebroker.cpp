//董梦丹 4-25
//最后修改于 4-27
#include "audiencebroker.h"
#include "audience.h"
#include "collection.h"
#include "record.h"

std::shared_ptr<AudienceBroker> AudienceBroker::m_instance =
        std::make_shared<AudienceBroker>(AudienceBroker());

bool AudienceBroker::verifyLoginInfo(std::string n, std::string p)
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
                std::vector<std::string> audienceRows;
                for(unsigned int i=0;i<mysql_num_fields(result);++i){
                    audienceRows.push_back(std::string(row[i]));
                }
                Audience a;
                a.setName(audienceRows[0]);
                a.setPassword(audienceRows[1]);
                a.setAvatar(audienceRows[2]);
                loginedAudiences.push_back(a);
                std::cout << "----------yes!!!!" << std::endl;
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

bool AudienceBroker::logoutAudience(std::string n)
{
    for(auto it = loginedAudiences.begin();it != loginedAudiences.end();){
        if((*it).getName() == n){
            it = loginedAudiences.erase(it);
            std::cout << "已退出" << std::endl;
            return true;
        }else{
            ++it;
        }
    }
}

bool AudienceBroker::checkLoginaudience(std::string n, std::string p)
{
    int flag = 0;
    for(auto a:loginedAudiences){
        if(a.getName() == n && a.getPassword() == p){
            flag = 1;
            return false;
        }
    }

    if(flag == 0){
        return true;
    }
}

std::string AudienceBroker::getAudienceAvatar(std::string n)
{
    std::string avatar;
    for(auto a:loginedAudiences){
        if(a.getName() == n){
            avatar = a.getAvatar();
        }
    }

    return avatar;
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

AudienceBroker::AudienceBroker()
{

}
