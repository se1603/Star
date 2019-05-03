#include "movieandtelevisionbroker.h"
#include <iostream>
#include "film.h"

using std::cout;    using std::endl;
using std::vector;  using std::string;

std::shared_ptr<MovieAndTelevisionBroker> MovieAndTelevisionBroker::m_instance = std::make_shared<MovieAndTelevisionBroker>(MovieAndTelevisionBroker());

MovieAndTelevisionBroker::MovieAndTelevisionBroker()
{
    initFilms();
}

std::map<std::string, std::vector<MovieAndTelevision> > MovieAndTelevisionBroker::getAllMovieAndTelevision() const
{
    return m_movieAndTelevision;
}

std::vector<Film> MovieAndTelevisionBroker::getFilms(FilmType type)
{
    std::vector<Film> result;
    for(int i = 0; i != m_films.size();i++)
    {
        Film tmp = m_films[i];
        if(tmp.type() == type)
        {
            result.push_back(tmp);
        }
    }
    return result;
}

void MovieAndTelevisionBroker::initFilms()
{
    if(!m_films.empty())
        m_films.clear();

    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0))
    {
        cout << "Connect MYSQL failed." << endl;
    }
    else{
        cout << "Connect MYSQL succed." << endl;
    }

    std::string sql = "select * from Film;";
    if(mysql_query(mysql,sql.data())){
        cout << "获取目录失败" << endl;
    }
    else{
        result = mysql_use_result(mysql);
        while(1){
            row = mysql_fetch_row(result);  //获取下一行
            if(row == nullptr) break;
            std::vector<std::string> res;
            for(unsigned int i = 0;i < mysql_num_fields(result);++i){
                std::cout << row[i] << std::endl;
                res.push_back(row[i]);
            }
            Film f = handleFilm(res);
            m_films.push_back(f);
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr)
        mysql_close(mysql);
    mysql_library_end();
}

Film MovieAndTelevisionBroker::handleFilm(std::vector<std::string> row)
{
    Film film;

    film.setName(row[0]);
    film.setType(atoi(row[1].c_str()));
    film.setRegion(atoi(row[2].c_str()));
    std::vector<std::string> director,actor,post;
    splictString(row[3],director,",");
    splictString(row[4],actor,",");
    splictString(row[5],post,",");
    film.setDirector(director);
    film.setActors(actor);
    film.setPost(post);
    film.setIntroduction(row[6]);
    film.setRecommend(atoi(row[7].c_str()));

    return film;
}

void MovieAndTelevisionBroker::splictString(const std::string &s, std::vector<std::string> &v, const std::string &c)
{
    std::string::size_type pos1, pos2;
        pos2 = s.find(c);
        pos1 = 0;
        while(std::string::npos != pos2)
        {
            v.push_back(s.substr(pos1, pos2-pos1));

            pos1 = pos2 + c.size();
            pos2 = s.find(c, pos1);
        }
        if(pos1 != s.length())
            v.push_back(s.substr(pos1));
}
