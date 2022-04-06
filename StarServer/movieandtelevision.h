#ifndef MOVIEANDTELEVISION_H
#define MOVIEANDTELEVISION_H

#include <vector>
#include "actor.h"
#include "director.h"
#include <map>

class MovieAndTelevision
{
public:
    MovieAndTelevision();

    //用户操作
    //判断
    bool isSame(std::string n);
    //收藏与记录
    void showInfo(std::vector<std::string> &a_collections);

    void searchInfo(std::vector<std::string> &vec);

protected:
    std::string m_name;             //名称
    std::string m_introduction;       //简介
    Region m_region;                   //地区
    std::vector<std::string> m_post;  //海报
    std::vector<Actor *> m_actors;      //演员
    std::vector<Director *> m_director; //导演
    int m_episode; //集数

    std::vector<int> m_recommend;     //推荐标记
};

#endif // MOVIEANDTELEVISION_H
