/* Author:王梦娟
 * Date:2019-4-25
 * Note:影视代管者类
*/
#ifndef MOVIEANDTELEVISIONBROKER_H
#define MOVIEANDTELEVISIONBROKER_H

#include "relationalbroker.h"
#include "film.h"

class MovieAndTelevisionBroker : public RelationalBroker
{
public:
    static std::shared_ptr<MovieAndTelevisionBroker> getInstance()
    {
        return m_instance;
    }

    void initFilms();    //获取所有电影
    Film handleFilm(std::vector<std::string> row);   //处理数据库数据
    void splictString(const std::string& s, std::vector<std::string>& v, const std::string& c);


    std::vector<Film> getFilms(FilmType type);
    std::vector<Film> getRecommendFilms(int type);

private:
    MovieAndTelevisionBroker();
    static std::shared_ptr<MovieAndTelevisionBroker> m_instance;
    std::vector<Film> m_films;   //电影
};

#endif // MOVIEANDTELEVISIONBROKER_H
