/* Author:王梦娟
 * Date:2019-4-25
 * Note:影视代管者类
*/
#ifndef MOVIEANDTELEVISIONBROKER_H
#define MOVIEANDTELEVISIONBROKER_H

#include "relationalbroker.h"
#include "film.h"
#include "variety.h"
#include "comic.h"

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

    //综艺
    void initVarieties();
    Variety handleVariety(std::vector<std::string> row);

    std::vector<Variety> getVarieties(VarietyType type);
    std::vector<Variety> getRecommendVarieties(int type);


    //动漫
    void initComics();//获取所有动漫
    Comic handleComic(std::vector<std::string> row); //处理数据库数据

    std::vector<Comic> getComics(ComicType type);
    std::vector<Comic> getRecommendComics(int type);

//    std::vector<std::string> getVideoInfo(std::string name);
    std::vector<std::string> getVideoInfo(std::string name,int i);

private:
    MovieAndTelevisionBroker();
    static std::shared_ptr<MovieAndTelevisionBroker> m_instance;
    std::vector<Film> m_films;   //电影

    std::vector<Variety> m_varieties; //综艺
    std::vector<Comic> m_comics;  //动漫
};

#endif // MOVIEANDTELEVISIONBROKER_H
