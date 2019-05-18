#include "drame.h"


Drame::Drame(std::string name, std::string introduction, Region region, std::vector<std::string> posts, std::vector<Actor *> actors, std::vector<Director *> directors, std::vector<DrameType> types, int episode, std::vector<int> recommends)
{
    m_name = name;
    m_introduction = introduction;
    m_region = region;
    m_post = posts;
    m_actors = actors;
    m_director = directors;
    m_type = types;
    m_recommend = recommends;
    m_episode = episode;
}

std::vector<std::string> Drame::show(bool recommend)
{
    std::vector<std::string> showdrame;

       showdrame.push_back(m_name);
       if(recommend)
           showdrame.push_back(m_post[1]);
       else {
           showdrame.push_back(m_post[0]);
       }
       return  showdrame;
}

void Drame::findDrameByType(DrameType type, std::vector<Drame> &drames)
{
    for(auto t : m_type)
        {
            if(t == type)
                drames.push_back(*this);
    }
}

void Drame::findDrameByRecommend(int recommend, std::vector<Drame> &drames)
{
    for(auto c:m_recommend){
            if(c == recommend){
                drames.push_back(*this);
            }
    }
}

bool Drame::findByName(std::string name)
{
    if(m_name == name){
        return true;
    }else{
        return false;
    }
}

void Drame::recodeInfo(std::string name, std::vector<std::string> &v)
{
    if(m_name == name){
        auto i = std::to_string(m_episode);
        v.push_back(i);
        v.push_back(m_introduction);
        v.push_back("2");
        for(auto t: m_type){
            switch(t){
            case DrameType::Family:{
                v.push_back("家庭");
                break;
            }
            case DrameType::MartialArts:{
                v.push_back("武侠");
                break;
            }
            case DrameType::AncientCostume:{
                v.push_back("古装");
                break;
            }
            case DrameType::History:{
                v.push_back("历史");
                break;
            }
            case DrameType::Idol:{
                v.push_back("偶像");
                break;
            }
            case DrameType::Metropolis:{
                v.push_back("都市");
                break;
            }
            case DrameType::Suspense:{
                v.push_back("悬疑");
                break;
            }
            default:v.push_back("科幻");
                break;
            }
        }
    }else{
        return;
    }
}

void Drame::save(std::map<std::string, Drame> &drames)
{
    drames[m_name] = *this;
}

