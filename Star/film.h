#ifndef FILM_H
#define FILM_H

#include "movieandtelevision.h"

enum class FilmType
{
    Recommend = 0,
    MartialArts = 1,    //武侠
    Suspense = 2,       //悬疑
    Comedy = 3,         //喜剧
    Action = 4,         //动作
    Love = 5,           //爱情
    Cartoon = 6,        //动画
    Terror = 7,         //惊悚
    ScienceFiction = 8  //科幻
};

class Film : public MovieAndTelevision
{
public:
    Film(std::string name,std::string introduction,
         Region region,std::vector<std::string> posts,
         std::vector<std::string> actors,
         std::vector<std::string> directors,std::vector<FilmType> types,
         std::vector<int> recommends);


    std::vector<std::string> show(bool recommend);  //电影显示的消息
    void findFilmByType(FilmType type, std::vector<Film> &films);  //获取该类电影
    void findFilmByRecommend(int recommend,std::vector<Film> &films); //获取该类推荐下的电影

private:
    std::vector<FilmType> m_type;
};
#endif // FILM_H
