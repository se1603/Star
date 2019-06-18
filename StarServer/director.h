/* Author:王梦娟
 * Date:2019-4-26
 * Note:导演
 * author：古长蓉
 * data：2019-06-17 增加搜索导演函数
*/
#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <string>
#include "region.h"
#include <vector>

class MovieAndTelevision;

class Director
{
public:
    Director(std::vector<std::string> paramters,Region region);
    Director(std::string name);
    Director();

    void addMovieAndTelevision(MovieAndTelevision *movieAndTelevision);
    //查找导演信息
     bool findByName(std::string name);
     void searchInfo(std::vector<std::string> &vec);

    void directorInfo(std::vector<std::string> &v);//导演信息
private:
    std::string m_name;
    std::string m_birthday;
    Region m_region;
    std::string m_introduction;
    std::string m_photo;
    std::vector<MovieAndTelevision *> m_movieAndTelevision;  //影视
};

#endif // DIRECTOR_H
