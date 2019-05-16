#include "comic.h"

Comic::Comic(std::string name, std::string introduction, Region region, std::vector<std::string> posts, std::vector<Actor *> actors, std::vector<Director *> directors, std::vector<ComicType> types, int episode, std::vector<int> recommends)
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

void Comic::recodeInfo(std::string name, std::vector<std::string> &v)
{
    if(m_name == name){
        auto i = std::to_string(m_episode);
        v.push_back(i);
        for(auto t: m_type){
            if(t == ComicType::Campus){
                v.push_back("校园");
            }
            if(t == ComicType::WarmBlood){
                v.push_back("热血");
            }
            if(t== ComicType::RobotWars){
                 v.push_back("机战");
            }
            if(t== ComicType::Kayoing){
                v.push_back("美少女");
            }
            if(t == ComicType::Combat){
                v.push_back("格斗");
            }
            if(t == ComicType::Love){
                 v.push_back("恋爱");
            }
            if(t == ComicType::Youth){
                v.push_back("青春");
            }
//            switch(t){
//            case ComicType::Campus:{
//                v.push_back("校园");
//                break;
//            }
//            case ComicType::WarmBlood:{
//                v.push_back("动画");
//                break;
//            }
//            case ComicType::RobotWars:{
//                v.push_back("机战");
//                break;
//            }
//            case ComicType::Kayoing:{
//                v.push_back("美少女");
//                break;
//            }
//            case ComicType::Combat:{
//                v.push_back("格斗");
//                break;
//            }
//            case ComicType::Love:{
//                v.push_back("恋爱");
//                break;
//            }
//            default:v.push_back("热血");
//                break;
//            }
        }
    }else{
        return;
    }
}

bool Comic::findByName(std::string name)
{
    if(m_name == name){
        return true;
    }else{
        return false;
    }
}

void Comic::save(std::map<std::string, Comic> &comics)
{
    comics[m_name] = *this;
}
