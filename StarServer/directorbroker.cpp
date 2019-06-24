#include "directorbroker.h"
/*author：古长蓉
 * data：2019-06-24   从movieandtelevisionbroker中分离actorbroker
 */
#include <iostream>

DirectorBroker* DirectorBroker::m_instance = new DirectorBroker();

DirectorBroker::DirectorBroker()
{
    initDirectors();
}

DirectorBroker::~DirectorBroker()
{
    delete m_instance;
}

void DirectorBroker::initDirectors()
{
    if(!m_directors.empty())
        m_directors.clear();

    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0))
    {
        std::cout << "Connect MYSQL failed." << std::endl;
    }
    else{
        std::cout << "Connect MYSQL succed." << std::endl;
    }

    std::string sql = "select * from Director;";
    if(mysql_query(mysql,sql.data())){
        std::cout << "获取目录失败" << std::endl;
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
            Director d = handleDirector(res);
            m_directors[row[0]] = d;
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr)
        mysql_close(mysql);
    mysql_library_end();
}

Director DirectorBroker::handleDirector(std::vector<std::string> row)
{
    std::vector<std::string> paramters;
    std::string name,birthday,introduction,photo;

    Region region;

    name = row[0];
    birthday = row[1];
    introduction = row[3];
    photo = row[4];

    switch (atoi(row[2].c_str())) {
    case 1:
        region = Region::China;
        break;
    case 2:
        region = Region::American;
        break;
    case 3:
        region = Region::Korea;
        break;
    case 4:
        region = Region::India;
        break;
    case 5:
        region = Region::THailand;
        break;
    case 6:
        region = Region::Britain;
        break;
    case 7:
        region = Region::Japan;
        break;
    default:
        break;
    }
    paramters.push_back(name);
    paramters.push_back(birthday);
    paramters.push_back(photo);
    paramters.push_back(introduction);

    Director d = Director(paramters,region);
    return d;
}

std::vector<Director *> DirectorBroker::findDirector(std::vector<std::string> directors)
{
    std::vector<Director *> result;
    for(int i = 0; i != directors.size();i++)
    {
        auto it = m_directors.find(directors[i]);
        if(it != m_directors.end())
        {
            result.push_back(&it->second);
        }
        else {
            Director d = Director(directors[i]);
            m_directors[directors[i]] = d;
            result.push_back(&m_directors[directors[i]]);
        }
    }
    return result;
}

void DirectorBroker::addMovieAndTelevision(std::vector<std::string> directors, MovieAndTelevision &mat)
{
    for (int i = 0;i != directors.size();i ++)
    {
        auto it = m_directors.find(directors[i]);
        if(it != m_directors.end())
        {
            it->second.addMovieAndTelevision(&mat);
        }
    }
}

std::vector<Director *> DirectorBroker::searchDirector(std::string name)
{
    std::vector<Director *> p;
    for(auto it = m_directors.begin(); it != m_directors.end(); it++){
        if(it->second.findByName(name)){
            p.push_back(&it->second);
        }
    }
    return p;
}


