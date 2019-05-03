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
    Film handleFilm(std::vector<std::string> row);   //存储电影前的处理
    void splictString(const std::string& s, std::vector<std::string>& v, const std::string& c);

    std::map<std::string, std::vector<MovieAndTelevision> > getAllMovieAndTelevision() const;

    std::vector<Film> getFilms(FilmType type);

private:
    MovieAndTelevisionBroker();
    static std::shared_ptr<MovieAndTelevisionBroker> m_instance;
    std::map<std::string,std::vector<MovieAndTelevision>> m_movieAndTelevision;
    std::vector<Film> m_films;
};

#endif // MOVIEANDTELEVISIONBROKER_H
