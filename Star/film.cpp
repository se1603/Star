#include "film.h"

Film::Film(std::string name, std::string introduction, Region region, std::vector<std::string> posts, std::vector<std::string> actors, std::vector<std::string> directors, std::vector<FilmType> types, std::vector<int> recommends)
{
    m_name = name;
    m_introduction = introduction;
    m_region = region;
    m_post = posts;
    m_actors = actors;
    m_director = directors;
    m_type = types;
    m_recommend = recommends;
    m_episode = 1;
}

std::vector<std::string> Film::show(bool recommend)
{
    std::vector<std::string> showfilm;

    showfilm.push_back(m_name);
    if(recommend)
        showfilm.push_back(m_post[1]);
    else {
        showfilm.push_back(m_post[0]);
    }
    return  showfilm;
}

void Film::findFilmByType(FilmType type,std::vector<Film> &films)
{
    for(auto t : m_type)
    {
        if(t == type)
            films.push_back(*this);
    }
}

void Film::findFilmByRecommend(int recommend, std::vector<Film> &films)
{
    for(auto t : m_recommend)
    {
        if(t == recommend)
            films.push_back(*this);
    }
}

