#include "film.h"

Film::Film(std::string name, std::string introduction, Region region, std::vector<std::string> posts, std::vector<Actor *> actors, std::vector<Director *> directors, std::vector<FilmType> types, std::vector<int> recommends)
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

Film::Film()
{

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

void Film::recodeInfo(std::string name, std::vector<std::string> &v)
{
//    std::vector<std::string> showfilm;

    if(m_name == name){
        auto i = std::to_string(m_episode);
        v.push_back(i);
        v.push_back(m_introduction);
        v.push_back("1");
        auto regin = m_region;
        switch(regin){
        case Region::American:{
            v.push_back("美国");
            break;
        }
        case Region::Britain:{
            v.push_back("英国");
            break;
        }
        case Region::China:{
            v.push_back("中国");
            break;
        }
        case Region::India:{
            v.push_back("印度");
            break;
        }
        case Region::Korea:{
            v.push_back("韩国");
            break;
        }
        case Region::THailand:{
            v.push_back("泰国");
            break;
        }
        case Region::Japan:{
            v.push_back("日本");
            break;
        }
        default:break;
        }
        for(auto t: m_type){
            switch(t){
            case FilmType::Action:{
                v.push_back("动作");
                break;
            }
            case FilmType::MartialArts:{
                v.push_back("武侠");
                break;
            }
            case FilmType::Cartoon:{
                v.push_back("动画");
                break;
            }
            case FilmType::Comedy:{
                v.push_back("喜剧");
                break;
            }
            case FilmType::Suspense:{
                v.push_back("悬疑");
                break;
            }
            case FilmType::Terror:{
                v.push_back("惊悚");
                break;
            }
            case FilmType::Love:{
                v.push_back("爱情");
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

void Film::getActorInfo(std::string name, std::vector<std::string> &v)
{
    std::vector<std::string> resource;

    auto a = m_actors;

    for(int i = 0;i != a.size();i++){
        auto tem = a[i];
        tem->actorInfo(resource);
    }

    auto d = m_director;
    for(int i = 0;i != d.size();i++){
        auto tem = d[i];
        tem->directorInfo(resource);
    }
    v = resource;
}
bool Film::findByName(std::string name)
{
    if(m_name == name){
        return true;
    }else{
        return false;
    }
}

void Film::save(std::map<std::string, Film> &films)
{
    films[m_name] = *this;
}

//MartialArts = 1,    //武侠
//Suspense = 2,       //悬疑
//Comedy = 3,         //喜剧
//Action = 4,         //动作
//Love = 5,           //爱情
//Cartoon = 6,        //动画
//Terror = 7,         //惊悚
//ScienceFiction = 8  //科幻
