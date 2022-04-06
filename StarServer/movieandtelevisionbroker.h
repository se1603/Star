#ifndef MOVIEANDTELEVISIONBROKER_H
#define MOVIEANDTELEVISIONBROKER_H

#include "relationalbroker.h"
#include "film.h"
#include "variety.h"
#include "comic.h"
#include "drame.h"
#include "record.h"
#include "actorbroker.h"
#include "directorbroker.h"

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
    std::vector<std::string> getVideoInfo(std::string name);//获取影视内容
    

    //用户操作
    //处理用户信息
    void processAudienceCollection(std::vector<std::string> tmp,MovieAndTelevision *m);
    void processAudienceRecord(std::vector<std::string> tmp,MovieAndTelevision *m);
    //获取用户具体信息
    void showCollection(MovieAndTelevision* m, std::vector<std::string> &collections);
    void showRecord(MovieAndTelevision* m, std::vector<std::string> &records);
//获取导演和演员信息
     std::vector<std::string> getActorInfo(std::string name);
     //查找影视，并获取指针提供给评论代管类
     void findMovieandTelevision(std::string name,MovieAndTelevision* m);

     //搜索
     std::vector<Film *> searchFilm(std::string name); //从map中读取数据，返回给controller
     std::vector<Drame *> searchDrama(std::string name);
     std::vector<Comic *> searchComic(std::string name);

     //本地浏览记录
     bool addBrowseRecord(std::string recordName, std::string startTime,
                          std::string duration, std::string type);
     std::string getBrowseRecord();
private:
    MovieAndTelevisionBroker();
    static MovieAndTelevisionBroker *m_instance;
    ActorBroker *m_actorBroker;
    DirectorBroker *m_directorBroker;
    std::map<std::string,Film> m_films;   //电影
    std::map<std::string,Drame> m_drames;  //剧集
    std::map<std::string,Variety> m_varieties; //综艺
    std::map<std::string,Comic> m_comics;  //动漫
    std::vector<Record> browse_records;
};

#endif // MOVIEANDTELEVISIONBROKER_H
