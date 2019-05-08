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

std::vector<Film> MovieAndTelevisionBroker::getFilms(FilmType type)
{
    std::vector<Film> result;
    for(int i = 0; i != m_films.size();i++)
    {
        Film tmp = m_films[i];
        tmp.findFilmByType(type,result);
    }
    return result;
}

std::vector<Film> MovieAndTelevisionBroker::getRecommendFilms(int type)
{
    std::vector<Film> result;
    for(int i = 0; i != m_films.size();i++)
    {
        Film tmp = m_films[i];
        tmp.findFilmByRecommend(type,result);
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
//                std::cout << row[i] << std::endl;
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
    std::vector<std::string> filmDirector,filmActor,filmPost,recommend,type;

    splictString(row[1],type,",");
    std::vector<FilmType> filmtype;     //电影类型
    for(int i = 0; i != type.size();i++)
    {
        switch (atoi(type[i].c_str())) {
        case 1:
            filmtype.push_back(FilmType::MartialArts);
            break;
        case 2:
            filmtype.push_back(FilmType::Suspense);
            break;
        case 3:
            filmtype.push_back(FilmType::Comedy);
            break;
        case 4:
            filmtype.push_back(FilmType::Action);
            break;
        case 5:
            filmtype.push_back(FilmType::Love);
            break;
        case 6:
            filmtype.push_back(FilmType::Cartoon);
            break;
        case 7:
            filmtype.push_back(FilmType::Terror);
            break;
        case 8:
            filmtype.push_back(FilmType::ScienceFiction);
            break;
        default:
            break;
        }
    }
    Region filmRegion = Region::China;
    switch (atoi(row[2].c_str())) {
    case 1:
        filmRegion = Region::China;
        break;
    case 2:
        filmRegion = Region::American;
        break;
    case 3:
        filmRegion = Region::Korea;
        break;
    case 4:
        filmRegion = Region::India;
        break;
    case 5:
        filmRegion = Region::THailand;
        break;
    case 6:
        filmRegion = Region::Britain;
        break;
    default:
        break;
    }
    splictString(row[3],filmDirector,",");
    splictString(row[4],filmActor,",");
    splictString(row[5],filmPost,",");
    splictString(row[7],recommend,",");
    std::vector<int> filmRecommends;
    for(int i = 0; i != recommend.size();i++)
    {
        filmRecommends.push_back(atoi(recommend[i].c_str()));
    }

    Film film(row[0],row[6],filmRegion,filmPost,
            filmActor,filmDirector,filmtype,filmRecommends);
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
