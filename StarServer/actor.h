/* Author:王梦娟
 * Date:2019-4-25
 * Note:演员
 * author:古长蓉
 * data:2019-06-17 增加搜索演员信息函数
*/
#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include "region.h"
#include <vector>

class MovieAndTelevision;

class Actor
{
public:
    Actor(std::vector<std::string> paramters,Region region);
    Actor(std::string name);
    Actor();

    //查找演员信息
    bool findByName(std::string name);

    void searchInfo(std::vector<std::string> &vec);

    void addMovieAndTelevision(MovieAndTelevision *movieAndTelevision);

    void actorInfo(std::vector<std::string> &vec);
private:
    std::string m_name;         //名字
    std::string m_birthday;     //生日
    Region m_region;            //地区
    std::string m_introduction;  //简介
    std::string m_photo; //演员
    std::vector<MovieAndTelevision *> m_movieAndTelevision;  //影视
};

#endif // ACTOR_H
