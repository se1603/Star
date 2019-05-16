#include "variety.h"


Variety::Variety(std::string name, std::string introduction, Region region,
                 std::vector<std::string> posts,
                 std::vector<Actor *> actors,
                 std::vector<Director *> directors,
                 std::vector<VarietyType> types, std::vector<int> recommends, int episodes)
{
    m_name = name;
    m_introduction = introduction;
    m_region = region;
    m_post = posts;
    m_actors = actors;
    m_director = directors;
    m_type = types;
    m_recommend = recommends;
    m_episode = episodes;
}

std::vector<std::string> Variety::show(bool recommend)
{
    std::vector<std::string> showvariety;
    showvariety.push_back(m_name);
    if(recommend)
        showvariety.push_back(m_post[1]);
    else
        showvariety.push_back(m_post[0]);

    return showvariety;
}

void Variety::findVarietyByType(VarietyType type, std::vector<Variety> &varieties)
{
    for(auto t: m_type){
        if(t == type)
            varieties.push_back(*this);
    }
}

void Variety::findVarietyByRecommend(int recommend, std::vector<Variety> &varieties)
{
    for(auto r: m_recommend){
        if(r == recommend)
            varieties.push_back(*this);
    }
}

void Variety::recodeInfo(std::string name, std::vector<std::string> &v)
{
    if(m_name == name){
        auto i = std::to_string(m_episode);
        v.push_back(i);
        for(auto t: m_type){
            switch(t){
            case VarietyType::Food:{
                v.push_back("美食");
                break;
            }
            case VarietyType::Funny :{
                v.push_back("搞笑");
                break;
            }
            case VarietyType::Interview :{
                v.push_back("访谈");
                break;
            }
            case VarietyType::RealityShow:{
                v.push_back("真人秀");
                break;
            }
            case VarietyType::TalentShow:{
                v.push_back("悬疑");
                break;
            }
            case VarietyType::Travel:{
                v.push_back("旅游");
                break;
            }
            case VarietyType::ActualRecord:{
                v.push_back("纪实");
                break;
            }
            default:v.push_back("选秀");
                break;
            }
        }
    }else{
        return;
    }
}

bool Variety::findByName(std::string name)
{
    if(m_name == name){
        return true;
    }else{
        return false;
    }
}

void Variety::save(std::map<std::string, Variety> &varietys)
{
    varietys[m_name] = *this;
}
