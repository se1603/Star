#include "drame.h"


Drame::Drame(std::string name, std::string introduction, Region region, std::vector<std::string> posts, std::vector<std::string> actors, std::vector<std::string> directors, std::vector<DrameType> types, int episode, std::vector<int> recommends)
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

