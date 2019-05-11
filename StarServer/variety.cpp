#include "variety.h"


Variety::Variety(std::string name, std::string introduction, Region region,
                 std::vector<std::string> posts,
                 std::vector<std::string> actors,
                 std::vector<std::string> directors,
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
