#include "movieandtelevisionbroker.h"
#include <iostream>
#include "film.h"
#include "variety.h"

using std::cout;    using std::endl;
using std::vector;  using std::string;

MovieAndTelevisionBroker* MovieAndTelevisionBroker::m_instance = new MovieAndTelevisionBroker();

MovieAndTelevisionBroker::MovieAndTelevisionBroker()
{
    initActors();
    initFilms();
    initVarieties();
    initComics();
    initDrame();
}

std::vector<Film> MovieAndTelevisionBroker::getFilms(FilmType type)
{
    std::vector<Film> result;
    for(auto it = m_films.begin(); it != m_films.end();it++)
    {
        Film tmp = it->second;
        tmp.findFilmByType(type,result);
    }
    return result;
}

std::vector<Film> MovieAndTelevisionBroker::getRecommendFilms(int type)
{
    std::vector<Film> result;
    for(auto it = m_films.begin(); it != m_films.end();it++)
    {
        Film tmp = it->second;
        tmp.findFilmByRecommend(type,result);
    }
    return result;
}

void MovieAndTelevisionBroker::initDrame()
{
    if(!m_drames.empty())
        m_drames.clear();

    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0)){
        cout << "(Drame)Connect MYSQL failed." << endl;
    }else{
        cout << "(Drame)Connect MYSQL succeed." << endl;
    }

    std::string sql = "select * from Drame;";
    if(mysql_query(mysql,sql.data())){
        cout << "(Drame)获取失败" << endl;
    }else{
        result = mysql_use_result(mysql);
        while(1){
            row = mysql_fetch_row(result);
            if(row == nullptr) break;
            std::vector<std::string> res;
            for(unsigned int i=0;i<mysql_num_fields(result);++i){
                res.push_back(row[i]);
                //                    cout << i << "  " << row[i] << endl;
            }
            Drame drame= handleDrame(res);
            drame.save(m_drames);
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr)
        mysql_close(mysql);
    mysql_library_end();
}

Drame MovieAndTelevisionBroker::handleDrame(std::vector<std::string> row)
{
    std::vector<std::string> drameDirector,drameActor,dramePost,recommend,type;

    splictString(row[1],type,",");
    std::vector<DrameType> drametype;     //剧集类型
    for(int i = 0; i != type.size();i++)
    {
        switch (atoi(type[i].c_str())) {
        case 1:
            drametype.push_back(DrameType::AncientCostume);
            break;
        case 2:
            drametype.push_back(DrameType::Suspense);
            break;
        case 3:
            drametype.push_back(DrameType::MartialArts);
            break;
        case 4:
            drametype.push_back(DrameType::Metropolis);
            break;
        case 5:
            drametype.push_back(DrameType::History);
            break;
        case 6:
            drametype.push_back(DrameType::Idol);
            break;
        case 7:
            drametype.push_back(DrameType::Family);
            break;
        case 8:
            drametype.push_back(DrameType::ScienceFiction);
            break;
        default:
            break;
        }
    }
    Region drameRegion = Region::China;
    switch (atoi(row[2].c_str())) {
    case 1:
        drameRegion = Region::China;
        break;
    case 2:
        drameRegion = Region::American;
        break;
    case 3:
        drameRegion = Region::Korea;
        break;
    case 4:
        drameRegion = Region::India;
        break;
    case 5:
        drameRegion = Region::THailand;
        break;
    case 6:
        drameRegion = Region::Britain;
        break;
    case 7:
        drameRegion = Region::Japan;
        break;
    default:
        break;
    }
    splictString(row[3],drameDirector,",");
    std::vector<Director *> directors;
    for(int i = 0; i != drameDirector.size();i++)
    {
        auto it = m_directors.find(drameDirector[i]);
        if(it != m_directors.end())
        {
            directors.push_back(&it->second);
        }
        else {
            Director d = Director(drameDirector[i]);
            m_directors[drameDirector[i]] = d;
            directors.push_back(&m_directors[drameDirector[i]]);
        }
    }

    splictString(row[4],drameActor,",");
    std::vector<Actor *> actors;
    for(int i = 0; i != drameActor.size();i++)
    {
        auto it = m_actors.find(drameActor[i]);
        if(it != m_actors.end())
        {
            actors.push_back(&it->second);
        }
        else {
            Actor tmpActor(drameActor[i]);
            m_actors[drameActor[i]] = tmpActor;
            actors.push_back(&m_actors[drameActor[i]]);
        }
    }

    splictString(row[5],dramePost,",");
    splictString(row[7],recommend,",");
    std::vector<int> drameRecommends;
    for(int i = 0; i != recommend.size();i++)
    {
        drameRecommends.push_back(atoi(recommend[i].c_str()));
    }

    Drame drame(row[0],row[6],drameRegion,dramePost,actors,directors,drametype,atoi(row[8].c_str()),drameRecommends);

    for (int i = 0;i != drameActor.size();i ++)
    {
        auto it = m_actors.find(drameActor[i]);
        if(it != m_actors.end())
        {
            it->second.addMovieAndTelevision(&drame);
        }
    }

    for (int i = 0;i != drameDirector.size();i ++)
    {
        auto it = m_directors.find(drameDirector[i]);
        if(it != m_directors.end())
        {
            it->second.addMovieAndTelevision(&drame);
        }
    }

    return drame;
}

std::vector<Drame> MovieAndTelevisionBroker::getDrames(DrameType type)
{
    std::vector<Drame> result;
    for(auto it = m_drames.begin(); it != m_drames.end();it++){
        Drame tmp = it->second;
        tmp.findDrameByType(type, result);
    }
    return result;
}

std::vector<Drame> MovieAndTelevisionBroker::getRecommendDrames(int type)
{
    std::vector<Drame> result;
    for(auto it = m_drames.begin(); it != m_drames.end();it++){
        Drame tmp = it->second;
        tmp.findDrameByRecommend(type,result);
    }
    return result;
}
void MovieAndTelevisionBroker::initVarieties()
{
    if(!m_varieties.empty())
        m_varieties.clear();

    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0)){
        cout << "(Variety)Connect MYSQL failed." << endl;
    }else{
        cout << "(Variety)Connect MYSQL succeed." << endl;
    }

    std::string sql = "select * from VarietyShow;";
    if(mysql_query(mysql,sql.data())){
        cout << "(Variety)获取失败" << endl;
    }else{
        result = mysql_use_result(mysql);
        while(1){
            row = mysql_fetch_row(result);
            if(row == nullptr) break;
            std::vector<std::string> res;
            for(unsigned int i=0;i<mysql_num_fields(result);++i){
                res.push_back(row[i]);
            }
            Variety v = handleVariety(res);
            v.save(m_varieties);
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr)
        mysql_close(mysql);
    mysql_library_end();
}

Variety MovieAndTelevisionBroker::handleVariety(std::vector<std::string> row)
{
    std::vector<std::string> varietyDirector,varietyActor,varietyPost,recommend,type;

    splictString(row[1],type,",");
    std::vector<VarietyType> varietytype;
    for(int i=0;i!=type.size();i++)
    {
        switch (atoi(type[i].c_str())) {
        case 1:
            varietytype.push_back(VarietyType::RealityShow);
            break;
        case 2:
            varietytype.push_back(VarietyType::TalentShow);
            break;
        case 3:
            varietytype.push_back(VarietyType::Food);
            break;
        case 4:
            varietytype.push_back(VarietyType::Travel);
            break;
        case 5:
            varietytype.push_back(VarietyType::ActualRecord);
            break;
        case 6:
            varietytype.push_back(VarietyType::Funny);
            break;
        case 7:
            varietytype.push_back(VarietyType::Interview);
            break;
        default:
            break;
        }
    }

    int varietyEpisodes = atoi(row[2].c_str());

    Region varietyRegion = Region::China;
    switch (atoi(row[3].c_str())) {
    case 1:
        varietyRegion = Region::China;
        break;
    case 2:
        varietyRegion = Region::American;
        break;
    case 3:
        varietyRegion = Region::Korea;
        break;
    case 4:
        varietyRegion = Region::India;
        break;
    case 5:
        varietyRegion = Region::THailand;
        break;
    case 6:
        varietyRegion = Region::Britain;
        break;
    default:
        break;
    }
    splictString(row[4],varietyDirector,",");
    std::vector<Director *> directors;
    for(int i = 0; i != varietyDirector.size();i++)
    {
        auto it = m_directors.find(varietyDirector[i]);
        if(it != m_directors.end())
        {
            directors.push_back(&it->second);
        }
        else {
            Director d = Director(varietyDirector[i]);
            m_directors[varietyDirector[i]] = d;
            directors.push_back(&m_directors[varietyDirector[i]]);
        }
    }
    splictString(row[5],varietyActor,"/");
    std::vector<Actor *> actors;
    for(int i = 0; i != varietyActor.size();i++)
    {
        auto it = m_actors.find(varietyActor[i]);
        if(it != m_actors.end())
        {
            actors.push_back(&it->second);
        }
        else {
            Actor tmpActor(varietyActor[i]);
            m_actors[varietyActor[i]] = tmpActor;
            actors.push_back(&m_actors[varietyActor[i]]);
        }
    }

    splictString(row[6],varietyPost,",");

    splictString(row[8],recommend,",");
    std::vector<int> varietyRecommends;
    for(int i=0;i!=recommend.size();i++){
        varietyRecommends.push_back(atoi(recommend[i].c_str()));
    }

    Variety variety(row[0],row[7],varietyRegion,varietyPost,actors,directors,
            varietytype,varietyRecommends,varietyEpisodes);
    for (int i = 0;i != varietyActor.size();i ++)
    {
        auto it = m_actors.find(varietyActor[i]);
        if(it != m_actors.end())
        {
            it->second.addMovieAndTelevision(&variety);
        }
    }

    for (int i = 0;i != varietyDirector.size();i ++)
    {
        auto it = m_directors.find(varietyDirector[i]);
        if(it != m_directors.end())
        {
            it->second.addMovieAndTelevision(&variety);
        }
    }
    return variety;
}

std::vector<Variety> MovieAndTelevisionBroker::getVarieties(VarietyType type)
{
    std::vector<Variety> result;
    for(auto it = m_varieties.begin(); it != m_varieties.end();it++){
        Variety tmp = it->second;
        tmp.findVarietyByType(type,result);
    }
    return result;
}

std::vector<Variety> MovieAndTelevisionBroker::getRecommendVarieties(int type)
{
    std::vector<Variety> result;
    for(auto it = m_varieties.begin(); it != m_varieties.end();it++){
        Variety tmp = it->second;
        tmp.findVarietyByRecommend(type,result);
    }
    return result;
}

void MovieAndTelevisionBroker::initComics()
{
    if(!m_comics.empty())
        m_comics.clear();
    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0))
    {
        cout << "Connect MYSQL failed." << endl;
    }else{
        cout << "Connect MYSQL succed." << endl;
    }

    std::string sql = "select * from Comic;";
    if(mysql_query(mysql,sql.data())){
        cout << "获取目录失败" << endl;
    }else{
        result = mysql_use_result(mysql);
        while(1){
            row = mysql_fetch_row(result);
            if(row == nullptr) break;
            std::vector<string> res;
            for(unsigned i = 0;i < mysql_num_fields(result);++i){
                //                cout << i << "  " << row[i] << endl;
                res.push_back(row[i]);
            }
            Comic c = handleComic(res);
            c.save(m_comics);
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr)
        mysql_close(mysql);
    mysql_library_end();
}

Comic MovieAndTelevisionBroker::handleComic(std::vector<std::string> row)
{
    std::vector<std::string> comicDirector,comicActor,comicPost,recommend,type;

    splictString(row[1],type,",");
    std::vector<ComicType> comictype;     //动漫类型
    for(int i = 0; i != type.size();i++)
    {
        switch (atoi(type[i].c_str())) {
        case 1:
            comictype.push_back(ComicType::RobotWars);
            break;
        case 2:
            comictype.push_back(ComicType::Youth);
            break;
        case 3:
            comictype.push_back(ComicType::Combat);
            break;
        case 4:
            comictype.push_back(ComicType::Love);
            break;
        case 5:
            comictype.push_back(ComicType::Kayoing);
            break;
        case 6:
            comictype.push_back(ComicType::WarmBlood);
            break;
        case 7:
            comictype.push_back(ComicType::Campus);
            break;
        default:
            break;
        }
    }
    Region comicRegion = Region::China;
    switch (atoi(row[2].c_str())) {
    case 1:
        comicRegion = Region::China;
        break;
    case 2:
        comicRegion = Region::American;
        break;
    case 3:
        comicRegion = Region::Korea;
        break;
    case 4:
        comicRegion = Region::India;
        break;
    case 5:
        comicRegion = Region::THailand;
        break;
    case 6:
        comicRegion = Region::Britain;
        break;
    case 7:
        comicRegion = Region::Japan;
        break;
    default:
        break;
    }
    splictString(row[4],comicDirector,",");
    std::vector<Director *> directors;
    for(int i = 0; i != comicDirector.size();i++)
    {
        auto it = m_directors.find(comicDirector[i]);
        if(it != m_directors.end())
        {
            directors.push_back(&it->second);
        }
        else {
            Director d = Director(comicDirector[i]);
            m_directors[comicDirector[i]] = d;
            directors.push_back(&m_directors[comicDirector[i]]);
        }
    }
    splictString(row[5],comicActor,",");
    std::vector<Actor *> actors;
    for(int i = 0; i != comicActor.size();i++)
    {
        auto it = m_actors.find(comicActor[i]);
        if(it != m_actors.end())
        {
            actors.push_back(&it->second);
        }
        else {
            Actor tmpActor(comicActor[i]);
            m_actors[comicActor[i]] = tmpActor;
            actors.push_back(&m_actors[comicActor[i]]);
        }
    }

    splictString(row[6],comicPost,",");

    splictString(row[8],recommend,",");
    std::vector<int> comicRecommends;
    for(int i = 0; i != recommend.size();i++)
    {
        comicRecommends.push_back(atoi(recommend[i].c_str()));
    }

    Comic comic(row[0],row[7],comicRegion,comicPost,actors,directors,comictype,atoi(row[3].c_str()),comicRecommends);

    for (int i = 0;i != comicActor.size();i ++)
    {
        auto it = m_actors.find(comicActor[i]);
        if(it != m_actors.end())
        {
            it->second.addMovieAndTelevision(&comic);
        }
    }

    for (int i = 0;i != comicDirector.size();i ++)
    {
        auto it = m_directors.find(comicDirector[i]);
        if(it != m_directors.end())
        {
            it->second.addMovieAndTelevision(&comic);
        }
    }

    return comic;
}

std::vector<Comic> MovieAndTelevisionBroker::getComics(ComicType type)
{
    std::vector<Comic> result;
    for(auto it = m_comics.begin(); it != m_comics.end();it++)
    {
        Comic tmp = it->second;
        tmp.findComicByType(type,result);
    }
    return result;
}

std::vector<Comic> MovieAndTelevisionBroker::getRecommendComics(int type)
{
    std::vector<Comic> result;
    for(auto it = m_comics.begin(); it != m_comics.end();it++){
        Comic tem = it->second;
        tem.findComicByRecommend(type,result);
    }
    return result;
}


std::vector<std::string> MovieAndTelevisionBroker::getVideoInfo(std::string name, int i)
{
    std::vector<std::string> resource;
    switch(i){
    case 0:{
        for(auto it = m_films.begin(); it != m_films.end();it++){
            auto tem = it->second;
            if(tem.findByName(name)){
                tem.recodeInfo(name,resource);
                break;
            }
        }
        for(auto it = m_drames.begin();it != m_drames.end()&&resource.size() == 0;it++){
            auto tem = it->second;
            if(tem.findByName(name)){
                tem.recodeInfo(name,resource);
                break;
            }
        }
        for(auto it = m_comics.begin(); it != m_comics.end()&& resource.size() == 0;it++){
            auto tem = it->second;
            if(tem.findByName(name)){
                tem.recodeInfo(name,resource);
                break;
            }
        }
        for(auto it = m_varieties.begin(); it != m_varieties.end()&& resource.size() == 0;it++){
            auto tem = it->second;
            if(tem.findByName(name)){
                tem.recodeInfo(name,resource);
                break;
            }
        }
    }
    case 1:{
        for(auto it = m_films.begin(); it != m_films.end();it++){
            auto tem = it->second;
            tem.recodeInfo(name,resource);
            if(resource.size() != 0){
                break;
            }
        }
        break;
    }
    case 2:{
        for(auto it = m_drames.begin();it != m_drames.end();it++){
            auto tem = it->second;
            tem.recodeInfo(name,resource);
            if(resource.size() != 0){
                break;
            }
        }
        break;
    }
    case 3:{
        for(auto it = m_comics.begin(); it != m_comics.end();it++){
            auto tem = it->second;
            tem.recodeInfo(name,resource);
            if(resource.size() != 0){
                break;
            }
        }
        break;
    }
    case 4:{
        for(auto it = m_varieties.begin(); it != m_varieties.end();it++){
            auto tem = it->second;
            tem.recodeInfo(name,resource);
            if(resource.size() != 0){
                break;
            }
        }
        break;
    }
    default:break;
    }
    return resource;
}

void MovieAndTelevisionBroker::initActors()
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

    std::string sql = "select * from Actor;";
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
            Actor a = handleActor(res);
            m_actors[row[0]] = a;
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr)
        mysql_close(mysql);
    mysql_library_end();
}

Actor MovieAndTelevisionBroker::handleActor(std::vector<std::string> row)
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
    paramters.push_back(introduction);
    paramters.push_back(photo);
    
    Actor a = Actor(paramters,region);
    return a;
}

Director MovieAndTelevisionBroker::handleDirector(std::vector<std::string> row)
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
    paramters.push_back(introduction);
    paramters.push_back(photo);

    Director d = Director(paramters,region);
    return d;
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
            f.save(m_films);
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
    std::vector<Director *> directors;
    for(int i = 0; i != filmDirector.size();i++)
    {
        auto it = m_directors.find(filmDirector[i]);
        if(it != m_directors.end())
        {
            directors.push_back(&it->second);
        }
        else {
            Director d = Director(filmDirector[i]);
            m_directors[filmDirector[i]] = d;
            directors.push_back(&m_directors[filmDirector[i]]);
        }
    }

    splictString(row[4],filmActor,",");
    std::vector<Actor *> actors;
    for(int i = 0; i != filmActor.size();i++)
    {
        auto it = m_actors.find(filmActor[i]);
        if(it != m_actors.end())
        {
            actors.push_back(&it->second);
        }
        else {
            Actor tmpActor(filmActor[i]);
            m_actors[filmActor[i]] = tmpActor;
            actors.push_back(&m_actors[filmActor[i]]);
        }
    }

    splictString(row[5],filmPost,",");
    splictString(row[7],recommend,",");
    std::vector<int> filmRecommends;
    for(int i = 0; i != recommend.size();i++)
    {
        filmRecommends.push_back(atoi(recommend[i].c_str()));
    }

    Film film(row[0],row[6],filmRegion,filmPost,
            actors,directors,filmtype,filmRecommends);
    for (int i = 0;i != filmActor.size();i ++)
    {
        auto it = m_actors.find(filmActor[i]);
        if(it != m_actors.end())
        {
            it->second.addMovieAndTelevision(&film);
        }
    }

    for (int i = 0;i != filmDirector.size();i ++)
    {
        auto it = m_directors.find(filmDirector[i]);
        if(it != m_directors.end())
        {
            it->second.addMovieAndTelevision(&film);
        }
    }

    return film;
}

MovieAndTelevisionBroker::~MovieAndTelevisionBroker()
{
    delete m_instance;
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
