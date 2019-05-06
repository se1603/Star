/* Author:王梦娟
 * Date:2019-5-5
 * Note:电影
 * */
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
    Film();

    FilmType type() const;
    void setType(int filmtype);

private:
    FilmType m_type;
};
#endif // FILM_H
