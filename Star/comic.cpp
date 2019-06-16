#include "comic.h"


Comic::Comic(std::string name, std::string introduction, Region region, std::vector<std::string> posts, std::vector<std::string> actors, std::vector<std::string> directors, std::vector<ComicType> types, int episode, std::vector<int> recommends)
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

std::vector<std::string> Comic::show(bool recommend)
{
    std::vector<std::string> showcomic;

    showcomic.push_back(m_name);
    if(recommend)
        showcomic.push_back(m_post[1]);
    else {
        showcomic.push_back(m_post[0]);
    }
    return  showcomic;
}

void Comic::findComicByType(ComicType type, std::vector<Comic> &comics)
{
    for(auto t : m_type)
    {
        if(t == type)
            comics.push_back(*this);
    }
}

void Comic::findComicByRecommend(int recommend, std::vector<Comic> &comics)
{
    for(auto c:m_recommend){
        if(c == recommend){
            comics.push_back(*this);
        }
    }
}
