#include "browseandwatchcontroller.h"
#include "json/json.h"

std::shared_ptr<BrowseAndWatchController> BrowseAndWatchController::m_instance = std::make_shared<BrowseAndWatchController>(BrowseAndWatchController());

BrowseAndWatchController::BrowseAndWatchController()
{
    m_movieAndTelevisionBroker = MovieAndTelevisionBroker::getInstance();
}

std::string BrowseAndWatchController::interface(int category, int type)
{
    std::string reply;
    switch (category) {
    case 1:  //电影子类别显示
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
    case 0:{//主页目录
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
    case 1:{ //电影目录
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

std::string BrowseAndWatchController::recommend(int category)
{
    std::string out;
    Json::Value root;

    root["request"] = "RECOMMEND";
    root["category"] = category;  //1 电影的推荐
    switch (category) {
    case 0:{

    }
        break;
    case 1:{//电影推荐页面
        std::vector<std::string> title1{"正在热播","热门华语大片","高人气好莱坞大片","经典高分港片","历年贺岁大片精选"};

        Json::Value filmarry;
        Json::Value commonFilm;
        for(int i = 0; i != 6;i++)
        {
            std::vector<Film> films = m_movieAndTelevisionBroker->getRecommendFilms(i);
            Json::Value arry;
            Json::Value item;
            for(int a = 0; a != films.size();a++)
            {
                std::vector<std::string> resource;
                Json::Value film;
                if(i == 0){
                    resource = films[a].show(true);
                    film["name"] = resource[0];
                    film["post"] = resource[1];
                    filmarry.append(film);   //存大图电影
                }
                else{
                    resource = films[a].show(false);
                    film["name"] = resource[0];
                    film["post"] = resource[1];
                    arry.append(film); //存小图电影
                }
                if(i != 0)
                {
                    item["title"] = title1[i - 1];
                    item["films"] = arry;
                }
            }
            if(i != 0)
                commonFilm["resource"].append(item);
        }
        root["secondRecommends"] = commonFilm;   //普通
        root["firstRecommends"] = filmarry;  //大图
        out = root.toStyledString();
    }
        break;
    default:
        break;
    }
    return out;
}


std::string BrowseAndWatchController::filmInterface(int type)
{
    FilmType filmtype;
    switch (type) {
    case 0:
        filmtype = FilmType::Recommend;
        break;
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
        std::vector<std::string> resource;
        resource = films[i].show(false);
        Json::Value item;
        item["name"] = resource[0];
        item["post"] = resource[1];
        arryObj.append(item);
    }
    root["movieAndTelevision"] = arryObj;
    std::string out = root.toStyledString();

    return out;
}


