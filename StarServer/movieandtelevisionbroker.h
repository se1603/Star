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
#include "drame.h"

class MovieAndTelevisionBroker : public RelationalBroker
{
public:
    static MovieAndTelevisionBroker* getInstance()
    {
        return m_instance;
    }

    ~MovieAndTelevisionBroker();

    void splictString(const std::string& s, std::vector<std::string>& v, const std::string& c);

    void initFilms();    //获取所有电影
    Film handleFilm(std::vector<std::string> row);   //处理数据库数据

    std::vector<Film> getFilms(FilmType type);
    std::vector<Film> getRecommendFilms(int type);
    //剧集
    void initDrame();
    Drame handleDrame(std::vector<std::string> row);

    std::vector<Drame> getDrames(DrameType type);
    std::vector<Drame> getRecommendDrames(int type);

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
    
    //演员
    void initActors();
    Actor handleActor(std::vector<std::string> row);
    
    //导演
    void initDirectors();
    Director handleDirector(std::vector<std::string> row);
    
    std::vector<Film *> Search(std::string name); //从map中读取数据，返回给controller

private:
    MovieAndTelevisionBroker();
    static MovieAndTelevisionBroker *m_instance;
    std::map<std::string,Film> m_films;   //电影
    std::map<std::string,Drame> m_drames;  //剧集
    std::map<std::string,Variety> m_varieties; //综艺
    std::map<std::string,Comic> m_comics;  //动漫

    std::map<std::string,Actor> m_actors; //演员
    std::map<std::string,Director> m_directors; //导演
};

#endif // MOVIEANDTELEVISIONBROKER_H
