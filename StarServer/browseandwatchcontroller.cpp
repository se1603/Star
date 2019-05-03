#include "browseandwatchcontroller.h"
#include "json/json.h"

std::shared_ptr<BrowseAndWatchController> BrowseAndWatchController::m_instance = std::make_shared<BrowseAndWatchController>(BrowseAndWatchController());

BrowseAndWatchController::BrowseAndWatchController()
{
    m_movieAndTelevisionBroker = MovieAndTelevisionBroker::getInstance();
}

std::map<std::string, std::vector<MovieAndTelevision> > BrowseAndWatchController::getAllMovieAndTeleVision()
{
    return  m_movieAndTelevisionBroker->getAllMovieAndTelevision();
}

std::string BrowseAndWatchController::interface(int category, int type)
{
    std::string reply;
    switch (category) {
    case 1:  //电影
        reply = filmInterface(type);
        break;
    default:
        break;
    }

    return reply;
}

std::string BrowseAndWatchController::category(int type)
{
    std::string out;
    Json::Value root;
    Json::Value arryObj;
    root["request"] = "CATEGORY";
    root["type"] = type;
    switch (type) {
    case 0:{
        std::vector<std::string> category1{"精选","电影","剧集","动漫","综艺"};
        for(int i = 0; i != 5;i++)
        {
            Json::Value item;
            item["category"] = category1[i];
            arryObj.append(item);
        }
        root["categorys"] = arryObj;
        out = root.toStyledString();
        break;
    }
    case 1:{
        std::vector<std::string> category2{"推荐","喜剧","武侠","动画","悬疑","爱情","科幻","惊悚","动作"};
        for(int i = 0; i != 9;i++)
        {
            Json::Value item;
            item["category"] = category2[i];
            arryObj.append(item);
        }
        root["categorys"] = arryObj;
        out = root.toStyledString();
        break;
    }
    }

    return out;
}


std::string BrowseAndWatchController::filmInterface(int type)
{
    FilmType filmtype;
    std::string showType;
    switch (type) {
    case 1:
        filmtype = FilmType::MartialArts;
        break;
    case 2:
        filmtype = FilmType::Suspense;
        break;
    case 3:
        filmtype = FilmType::Comedy;
        break;
    case 4:
        filmtype = FilmType::Action;
        break;
    case 5:
        filmtype = FilmType::Love;
        break;
    case 6:
        filmtype = FilmType::Cartoon;
        break;
    case 7:
        filmtype = FilmType::Terror;
        break;
    case 8:
        filmtype = FilmType::ScienceFiction;
        break;
    default:
        filmtype = FilmType::Recommend;
        break;
    }
    std::vector<Film> films;
    films = m_movieAndTelevisionBroker->getFilms(filmtype);

    Json::Value root;
    Json::Value arryObj;
    root["request"] = "INTERFACE";
    root["interface"] = 1;
    root["type"] = type;
    for(int i = 0; i != films.size();i++)
    {
        Json::Value item;
        item["name"] = films[i].name();
        item["post"] = films[i].post()[0];
        arryObj.append(item);
    }
    root["films"] = arryObj;
    std::string out = root.toStyledString();

    return out;
}


