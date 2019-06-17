//董梦丹 5-17
#include "audiencecontroller.h"
#include "json/json.h"
#include "movieandtelevisionbroker.h"

AudienceController* AudienceController::m_instance = new AudienceController();

AudienceController::~AudienceController()
{
    delete m_instance;
}

bool AudienceController::verifyAudience(std::string name, std::string password)
{
    std::vector<std::string> audienceInfo;
    bool res = m_audienceBroker->verifyLoginInfo(name,password,audienceInfo);

    if(res == false)
    {
        return false;
    }
    else
    {
        std::string aname = audienceInfo[0];
        std::vector<std::string> c,r;
        splictString(audienceInfo[3],c,"/");
        splictString(audienceInfo[4],r,"/");

        for(int i=0;i<c.size();i++)
        {
            MovieAndTelevision* mp = new MovieAndTelevision();
            std::vector<std::string> tmp;
            splictString(c[i],tmp," ");
            m_movieAndTelevisionBroker->processAudienceCollection(tmp,mp);
            if(mp!=nullptr){
                //                m_movieAndTelevisionBroker->showCollection(mp);
                m_audienceBroker->createAudienceCollection(aname,tmp[1],mp);
            }
        }

        for(int i=0;i<r.size();i++){
            MovieAndTelevision* ap = new MovieAndTelevision();
            std::vector<std::string> tmp;
            splictString(r[i],tmp," ");
            m_movieAndTelevisionBroker->processAudienceRecord(tmp,ap);
            if(ap!=nullptr){
                //                m_movieAndTelevisionBroker->showCollection(ap);
                m_audienceBroker->createAudienceRecord(aname,tmp[1],tmp[2],ap);
            }
        }

        return true;
    }
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

bool AudienceController::addAudienceCollection(std::string audiencename, std::string collectname, std::string collecttime, std::string collecttype)
{
    if(m_audienceBroker->addAudienceCollection(audiencename,collectname,collecttime,collecttype)
            == true){
        std::vector<std::string> tmp{collectname,collecttime,collecttype};
        MovieAndTelevision *mv = new MovieAndTelevision();
        m_movieAndTelevisionBroker->processAudienceCollection(tmp,mv);
        if(mv != nullptr)
            m_audienceBroker->createAudienceCollection(audiencename,collecttime,mv);
        return true;
    }
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

void AudienceController::audienceCollection(std::string name, std::vector<std::string> &collectlist)
{
    std::map<std::string,MovieAndTelevision*> collectionmap;
    m_audienceBroker->readAudienceCollection(name,collectionmap);

    if(collectionmap.size()!=0){
        for(auto iter = collectionmap.rbegin();iter != collectionmap.rend();iter++){
            collectlist.push_back(iter->first);
            std::cout << iter->first << std::endl;
            m_movieAndTelevisionBroker->showCollection(iter->second,collectlist);
        }
    }
}

void AudienceController::audienceRecord(std::string name, std::vector<std::string> &recordlist)
{
    std::map<std::string,MovieAndTelevision*> recordmap;
    m_audienceBroker->readAudienceRecord(name,recordmap);

    if(recordmap.size()!=0){
        for(auto iter = recordmap.rbegin();iter != recordmap.rend();iter++){
            std::string m = iter->first;
            splictString(m,recordlist,"/");
            m_movieAndTelevisionBroker->showRecord(iter->second,recordlist);
        }
    }
}

std::string AudienceController::pakageCollection(std::vector<std::string> a_collections)
{
    Json::Value root;
    Json::Value arry;
    root["request"] = "COLLECTIONINFO";
    if(a_collections.size()!=0){
        for(int i=0;i < a_collections.size(); i+=3){
            Json::Value value;
            value["name"] = a_collections[i+1];
            value["post"] = a_collections[i+2];
            value["collecttime"] = a_collections[i];
            arry.append(value);
        }
    }else{
        Json::Value value;
        value["name"] = "空";
        value["post"] = "空";
        value["collecttime"] = "空";
        arry.append(value);
    }
    root["collections"] = arry;
    root.toStyledString();
    std::string res = root.toStyledString();
    return res;
}

std::string AudienceController::pakageRecord(std::vector<std::string> a_records)
{
    Json::Value root;
    Json::Value arry;
    root["request"] = "RECORDINFO";
    if(a_records.size()!=0){
        for(int i=0;i < a_records.size(); i+=4){
            Json::Value value;
            value["name"] = a_records[i+2];
            value["post"] = a_records[i+3];
            value["startPlayTime"] = a_records[i];
            value["duration"] = a_records[i+1];
            arry.append(value);
        }
    }else{
        Json::Value value;
        value["name"] = "空";
        value["post"] = "空";
        value["startPlayTime"] = "空";
        value["duration"] = "空";
        arry.append(value);
    }
    root["records"] = arry;

    root.toStyledString();
    std::string res = root.toStyledString();
    return res;
}

void AudienceController::splictString(std::string &s, std::vector<std::string> &v, const std::string &c)
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

AudienceController::AudienceController()
{
    m_audienceBroker = AudienceBroker::getInstance();
    m_movieAndTelevisionBroker = MovieAndTelevisionBroker::getInstance();
}
