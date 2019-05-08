/* Author:王梦娟
 * Date:2019-4-25
 * Note:影视，抽象类。
*/
#ifndef MOVIEANDTELEVISION_H
#define MOVIEANDTELEVISION_H

#include <vector>
#include "actor.h"

class MovieAndTelevision
{
public:
    MovieAndTelevision();


protected:
    std::string m_name;             //名称
    std::string m_introduction;       //简介
    Region m_region;                   //地区
    std::vector<std::string> m_post;  //海报
    std::vector<std::string> m_actors;      //演员
    std::vector<std::string> m_director; //导演
    int m_episode; //集数

    std::vector<int> m_recommend;     //推荐标记
};

#endif // MOVIEANDTELEVISION_H
