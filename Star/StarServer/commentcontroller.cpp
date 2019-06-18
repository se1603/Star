#include "commentcontroller.h"
#include "json/json.h"
#include "iostream"

CommentController* CommentController::m_instance = new CommentController();
CommentController::~CommentController()
{
    delete m_instance;
}

std::string CommentController::getCommentInfo(std::string name)
{
    std::vector<std::string> vec;
    Json::Value values;
    Json::Value root;
    std::string out;
    root["request"] = "SHOWCOMMENT";
    root["name"] = name;
//    std::cout << "我静如commentControl"<< std::endl;
    if(m_commentBroker->CommentSize() == 0){
        std::vector<std::string> v;
        m_audienceBroker->initAudience();
        m_commentBroker->infoFromDataBase(v);
        for(int i = 0;i != v.size();i+=4){
             MovieAndTelevision* mp = new MovieAndTelevision();
             m_movieAndTelevisionBroker->findMovieandTelevision(v[i+1],mp);
             Audience* a = new Audience();
             m_audienceBroker->findAudience(v[i],a);
             m_commentBroker->initcomment(v[i+1],v[i+2],v[i+3],a,mp);
            Json::Value value;
            if(v[i+1] == name){
               value["audienceName"] = v[i];
               value["comment"] = v[i+2];
               value["time"] = v[i+3];
               values.append(value);
            }
        }

    } else{
        m_commentBroker->getCommentInfo(name,vec);
        if(vec.size() != 0){
            for(auto i = vec.size();i != 0;i-=3){
                Json::Value value;
                value["audienceName"] = vec[i-1];
                value["comment"] = vec[i-2];
                value["time"] = vec[i-3];
                values.append(value);
            }
        }
    }
    root["resource"] = values;
    out = root.toStyledString();
    std::cout << out << std::endl;
    return out;
}

bool CommentController::insertComment(std::string an, std::string mn, std::string t, std::string c)
{
    MovieAndTelevision* mp = new MovieAndTelevision();
    m_movieAndTelevisionBroker->findMovieandTelevision(mn,mp);
    Audience* a = new Audience();
    m_audienceBroker->findAudience(an,a);
    m_commentBroker->initcomment(mn,c,t,a,mp);
    if(m_commentBroker->insertComment(an,mn,t,c) == true){

        return true;
    }else{
        return false;
    }
}

std::string CommentController::goodCommentInfo(std::string name)
{
    std::vector<std::string> vec;
    Json::Value values;
    Json::Value root;
    std::string out;
    if(m_commentBroker->CommentSize()!=0){
        m_commentBroker->goodCommentInfo(name,vec);
        if(vec.size() != 0){
            for(auto i = vec.size();i != 0;i-=3){
                Json::Value value;
                value["audienceName"] = vec[i-1];
                value["comment"] = vec[i-2];
                value["time"] = vec[i-3];
                values.append(value);
            }
        }
    }
    root["resource"] = values;
    out = root.toStyledString();
    std::cout << out << std::endl;
    return out;
}

CommentController::CommentController()
{
    m_audienceBroker = AudienceBroker::getInstance();
    m_movieAndTelevisionBroker = MovieAndTelevisionBroker::getInstance();
    m_commentBroker = CommentBroker::getInstance();
}
