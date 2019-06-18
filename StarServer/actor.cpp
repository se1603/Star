/* Author:王梦娟
 * Date:2019-4-25
 * Note:演员
 * author:古长蓉
 * data:2019-06-17 增加搜索演员信息函数
*/
#include "actor.h"

Actor::Actor(std::vector<std::string> paramters, Region region)
{
    m_name = paramters[0];
    m_birthday = paramters[1];
    m_introduction = paramters[2];
    m_photo = paramters[3];
    m_region = region;
}

Actor::Actor(std::string name)
{
    m_name = name;
    m_birthday = "未知";
    m_introduction = "未知";
    m_photo = "未知";
}

Actor::Actor()
{
    m_name = " ";
    m_birthday = " ";
    m_introduction = " ";
    m_photo = "./actors/default.png";
}

void Actor::addMovieAndTelevision(MovieAndTelevision *movieAndTelevision)
{
    m_movieAndTelevision.push_back(movieAndTelevision);
}

bool Actor::findByName(std::string name)
{
    if(m_name == name){
        return true;
    }else{
        return false;
    }
}

void Actor::actorInfo(std::vector<std::string> &vec)
{
    vec.push_back(m_name);
    vec.push_back("演员");
    if(m_photo == "未知"){
        vec.push_back("./actors/default.png");
    }else{
       vec.push_back(m_photo);
    }
}

void Actor::searchInfo(std::vector<std::string> &vec)
{
    vec.push_back(m_name);
    vec.push_back(m_birthday);
    vec.push_back(m_introduction);
    vec.push_back(m_photo);
    auto regin = m_region;
    switch(regin){
    case Region::American:{
        vec.push_back("美国");
        break;
    }
    case Region::Britain:{
        vec.push_back("英国");
        break;
    }
    case Region::China:{
        vec.push_back("中国");
        break;
    }
    case Region::India:{
        vec.push_back("印度");
        break;
    }
    case Region::Korea:{
        vec.push_back("韩国");
        break;
    }
    case Region::THailand:{
        vec.push_back("泰国");
        break;
    }
    case Region::Japan:{
        vec.push_back("日本");
        break;
    }
    default:break;
    }
}
