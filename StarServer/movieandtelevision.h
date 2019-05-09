#ifndef MOVIEANDTELEVISION_H
#define MOVIEANDTELEVISION_H

#include <vector>
#include "actor.h"

class MovieAndTelevision
{
public:
    MovieAndTelevision();

    std::string name() const;
    void setName(const std::string &name);

    std::vector<std::string> post() const;
    void setPost(const std::vector<std::string> &post);

    std::string introduction() const;
    void setIntroduction(const std::string &introduction);

    Region region() const;
    void setRegion(int regiontype);


    std::vector<std::string> actors() const;
    void setActors(const std::vector<std::string> &actors);

    std::vector<std::string> director() const;
    void setDirector(const std::vector<std::string> &director);

    void setRecommend(int value);
    std::vector<int> getRecommend() const;

protected:
    std::string m_name;             //名称
    std::vector<std::string> m_post;  //海报
    std::string m_introduction;       //简介
    Region m_region;                   //地区
    std::vector<std::string> m_actors;      //演员
    std::vector<std::string> m_director; //导演
    std::vector<int> recommend;     //推荐标记
};

#endif // MOVIEANDTELEVISION_H
