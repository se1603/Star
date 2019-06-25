/* Author:王梦娟
 * Date:2019-4-26
 * Note:导演
 * author：古长蓉
 * data：2019-06-17 增加搜索导演函数
*/
#include "director.h"

Director::Director(std::vector<std::string> paramters, Region region)
{
    m_name = paramters[0];
    m_birthday = paramters[1];
    m_introduction = paramters[2];
    m_photo = paramters[3];
    m_region = region;
}

Director::Director(std::string name)
{
    m_name = name;
    m_birthday = "未知";
    m_introduction = "未知";
    m_photo = "未知";
}

Director::Director()
{
    m_name = " ";
    m_birthday = " ";
    m_introduction = " ";
    m_photo = "./directors/default.png";
}

bool Director::findByName(std::string name)
{
    if(m_name == name){
        return true;
    }else{
        return false;
    }
}

void Director::searchInfo(std::vector<std::string> &vec)
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

void Director::addMovieAndTelevision(MovieAndTelevision *movieAndTelevision)
{
    m_movieAndTelevision.push_back(movieAndTelevision);
}
void Director::directorInfo(std::vector<std::string> &v)
{
    v.push_back(m_name);
    v.push_back("导演");
    if(m_photo == "未知"){
        v.push_back("./directors/default.png");
    }else{
         v.push_back(m_photo);
    }
}
