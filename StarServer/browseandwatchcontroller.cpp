#include "browseandwatchcontroller.h"
#include "json/json.h"
#include <iostream>

BrowseAndWatchController* BrowseAndWatchController::m_instance = new BrowseAndWatchController();

BrowseAndWatchController::BrowseAndWatchController()
{
    m_rtspAddress = "10.253.25.97";
    m_actorbroker = ActorBroker::getInstance();
    m_directorbroker = DirectorBroker::getInstance();
    m_movieAndTelevisionBroker = MovieAndTelevisionBroker::getInstance();
}

BrowseAndWatchController::~BrowseAndWatchController()
{
    delete m_instance;
}

std::string BrowseAndWatchController::interface(int category, int type)
{
    std::string reply;
    switch (category) {
    case 1:  //电影子类别显示
        reply = filmInterface(type);
        break;
    case 2:    //剧集子类别显示
        reply = drameInterface(type);
        break;
    case 3:
        reply = comicInterface(type);
        break;
    case 4:
        //综艺子类别显示
        reply = varietyInterface(type);
        break;
    default:
        break;
    }

    return reply;
}
std::string BrowseAndWatchController::getVideoInfo(std::string name)
{
    Json::Value root;
    std::string out;
    root["request"] = "RECODE";
    root["name"] = name;
    auto f = m_movieAndTelevisionBroker->getVideoInfo(name);
    Json::Value value;
    Json::Value types;
    root["videotype"] = 1;
    for(int i = 0;i != f.size();i++){
        Json::Value type;
        if(i == 0){
            value["esipode"] = f[0];
        }else if(i == 1){
            value["introduction"] = f[1];
        }else if(i == 2){
            value["category"] = f[2];
        }else if(i==3){
            value["region"] = f[3];
        }
        else{
            type["type"] = f[i];
            types.append(type);
        }
    }
    value["videotype"] = types;
    root["resource"] = value;
    out = root.toStyledString();

    return out;
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
    case 2:{  //剧集目录
        std::vector<std::string> category3{"推荐","古装","悬疑","武侠","都市","历史","偶像", "家庭","科幻"};
        for(int i = 0; i != 9; i++)
        {
            Json::Value item;
            item["category"] = category3[i];
            arryObj.append(item);
        }
        root["categorys"] = arryObj;
        out = root.toStyledString();
        break;
    }
    case 3:{//动漫目录
        std::vector<std::string> category4{"推荐","机战","青春","格斗","恋爱","美少女","热血","校园"};
        for(int i = 0;i != 8;i++){
            Json::Value item;
            item["category"] = category4[i];
            arryObj.append(item);
        }
        root["categorys"] = arryObj;
        out = root.toStyledString();
        break;
    }
    case 4:{
        //综艺目录
        std::vector<std::string> category5{"推荐","真人秀","选秀","美食","旅游","纪实","搞笑","访谈"};
        for(int i=0;i!=8;i++){
            Json::Value item;
            item["category"] = category5[i];
            arryObj.append(item);
        }
        root["categorys"] = arryObj;
        out = root.toStyledString();
    }
        break;
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
        std::vector<std::string> title{"电影精选","剧集精选","动漫精选","综艺精选"};
        Json::Value selectarray;
        Json::Value selectcommon;
        std::vector<Film> films = m_movieAndTelevisionBroker->getRecommendFilms(7);
        for(int i = 0;i != films.size();i++){
            std::vector<std::string> resource;
            Json::Value film;
            resource = films[i].show(true);
            film["name"] = resource[0];
            film["post"] = resource[1];
            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            film["rtspURL"] = url;
            selectarray.append(film);
        }

        std::vector<Drame> drames = m_movieAndTelevisionBroker->getRecommendDrames(7);
        for(int i = 0;i != drames.size();i++){
            std::vector<std::string> resource;
            Json::Value drame;
            resource = drames[i].show(true);
            drame["name"] = resource[0];
            drame["post"] = resource[1];

            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            drame["rtspURL"] = url;
            selectarray.append(drame);
        }

        std::vector<Comic> comics = m_movieAndTelevisionBroker->getRecommendComics(7);
        for(int i = 0;i != comics.size();i++){
            std::vector<std::string> resource;
            Json::Value comic;
            resource = comics[i].show(true);
            comic["name"] = resource[0];
            comic["post"] = resource[1];

            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            comic["rtspURL"] = url;
            selectarray.append(comic);
        }

        std::vector<Variety> varieties = m_movieAndTelevisionBroker->getRecommendVarieties(7);
        for(int i = 0;i != varieties.size();i++){
            std::vector<std::string> resource;
            Json::Value varietie;
            resource = varieties[i].show(true);
            varietie["name"] = resource[0];
            varietie["post"] = resource[1];

            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            varietie["rtspURL"] = url;
            selectarray.append(varietie);
        }
        root["firstRecommends"] = selectarray;  //大图



        std::vector<Film> film1s = m_movieAndTelevisionBroker->getRecommendFilms(99);
        Json::Value arry;
        Json::Value item;
        for(int a = 0;a != 5;a++)
        {
            std::vector<std::string> resource;
            Json::Value film;
            resource = film1s[a].show(false);
            film["name"] = resource[0];
            film["post"] = resource[1];

            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            film["rtspURL"] = url;
            arry.append(film); //存小图电影
            //            a++;
        }
        item["title"] = title[0];
        item["films"] = arry;
        selectcommon["resource"].append(item);

        std::vector<Drame> drame1 = m_movieAndTelevisionBroker->getRecommendDrames(5);
        Json::Value arryd;
        for(int a = 0;a != 5;a++){
            std::vector<std::string> resource;
            Json::Value drame;
            resource = drame1[a].show(false);
            drame["name"] = resource[0];
            drame["post"] = resource[1];
            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            drame["rtspURL"] = url;
            arryd.append(drame);
        }
        item["title"] = title[1];
        item["films"] = arryd;
        selectcommon["resource"].append(item);

        std::vector<Comic> comic2s = m_movieAndTelevisionBroker->getRecommendComics(99);
        Json::Value arry1;
        for(int a = 0; a != 5;a++)
        {
            std::vector<std::string> resource;
            Json::Value film;
            resource = comic2s[a].show(false);
            film["name"] = resource[0];
            film["post"] = resource[1];
            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            film["rtspURL"] = url;
            arry1.append(film); //存小图电影
        }
        item["title"] = title[2];
        item["films"] = arry1;
        selectcommon["resource"].append(item);

        std::vector<Variety> vas = m_movieAndTelevisionBroker->getRecommendVarieties(99);
        Json::Value arry2;
        for(int a = 0; a != 5;a++)
        {
            std::vector<std::string> resource;
            Json::Value film;
            resource = vas[a].show(false);
            film["name"] = resource[0];
            film["post"] = resource[1];
            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            film["rtspURL"] = url;
            arry2.append(film); //存小图电影
        }
        item["title"] = title[3];
        item["films"] = arry2;
        selectcommon["resource"].append(item);

        root["secondRecommends"] = selectcommon;
        out = root.toStyledString();

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
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

                    film["rtspURL"] = url;
                    filmarry.append(film);   //存大图电影
                }
                else{
                    resource = films[a].show(false);
                    film["name"] = resource[0];
                    film["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

                    film["rtspURL"] = url;
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
    case 2:{//剧集推荐页面
        std::vector<std::string> title2{"正在热播","猜你喜欢","排行榜","卫视同步","偶像剧场"};

        Json::Value dramearry;
        Json::Value commonDrame;
        for(int i = 0; i != 6;i++)
        {
            std::vector<Drame> drames = m_movieAndTelevisionBroker->getRecommendDrames(i);
            Json::Value arry;
            Json::Value item;
            for(int a = 0; a != drames.size();a++)
            {
                std::vector<std::string> resource;
                Json::Value drame;
                if(i == 0){
                    resource = drames[a].show(true);
                    drame["name"] = resource[0];
                    drame["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
                    drame["rtspURL"] = url;
                    dramearry.append(drame);   //存大图
                }
                else{
                    resource = drames[a].show(false);
                    drame["name"] = resource[0];
                    drame["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
                    drame["rtspURL"] = url;
                    arry.append(drame); //存小图
                }
                if(i != 0)
                {
                    item["title"] = title2[i - 1];
                    item["drames"] = arry;
                }
            }
            if(i != 0)
                commonDrame["resource"].append(item);
        }
        root["secondRecommends"] = commonDrame;   //普通
        root["firstRecommends"] = dramearry;  //大图
        out = root.toStyledString();
    }
        break;
    case 3:{
        std::vector<std::string> title3{"正在热播","日漫推荐","国漫推荐","独家播放","经典日漫"};
        Json::Value comicarray;
        Json::Value commonComic;
        for(int i = 0;i != 6;i++){
            std::vector<Comic> comics = m_movieAndTelevisionBroker->getRecommendComics(i);
            Json::Value array;
            Json::Value item;
            for(int a = 0;a != comics.size();a++){
                std::vector<std::string> resource;
                Json::Value comic;
                if(i == 0){
                    resource = comics[a].show(true);
                    comic["name"] = resource[0];
                    comic["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
                    comic["rtspURL"] = url;
                    comicarray.append(comic);  //存大图电影
                }
                else{
                    resource = comics[a].show(false);
                    comic["name"] = resource[0];
                    comic["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
                    comic["rtspURL"] = url;
                    array.append(comic); //存小图电影
                }
                if(i != 0)
                {
                    item["title"] = title3[i - 1];
                    item["films"] = array;
                }
            }
            if(i != 0)
                commonComic["resource"].append(item);
        }
        root["secondRecommends"] = commonComic;   //普通
        root["firstRecommends"] = comicarray;  //大图
        out = root.toStyledString();
    }
        break;
    case 4:{
        std::vector<std::string> title4{"热门在播综艺","今日份快乐源泉请查收","地表最强真人秀","细说人生百态"};
        Json::Value varietyarry;
        Json::Value commonVariety;
        for(int i=0;i!=5;i++){
            std::vector<Variety> varieties = m_movieAndTelevisionBroker->getRecommendVarieties(i);
            Json::Value arry;
            Json::Value item;
            for(int a=0;a!=varieties.size();a++)
            {
                std::vector<std::string> resource;
                Json::Value variety;
                if(i == 0){
                    resource = varieties[a].show(true);
                    variety["name"] = resource[0];
                    variety["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

                    variety["rtspURL"] = url;
                    varietyarry.append(variety);
                }else{
                    resource = varieties[a].show(false);
                    variety["name"] = resource[0];
                    variety["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

                    variety["rtspURL"] = url;
                    arry.append(variety);
                }

                if(i!=0){
                    item["title"] = title4[i-1];
                    item["varieties"] = arry;
                }
            }
            if(i!=0)
                commonVariety["resource"].append(item);
        }
        root["secondRecommends"] = commonVariety;
        root["firstRecommends"] = varietyarry;
        out = root.toStyledString();
    }
        break;
    default:
        break;
    }
    return out;
}

std::string BrowseAndWatchController::getActorInfo(std::string name)
{
    Json::Value root;
    std::string out;

    root["request"] = "INFOMATION";
    root["name"] = name;

    auto info = m_movieAndTelevisionBroker->getActorInfo(name);
    Json::Value values;

    //    std::cout << "information"<<info.size() << std::endl;
    for(int i = 0;i != info.size();i+=3){
        Json::Value value;
        value["name"] = info[i];
        value["type"] = info[i+1];
        value["post"] = info[i+2];
        values.append(value);
    }
    root["resource"] = values;
    out = root.toStyledString();

    return out;
}

//std::string BrowseAndWatchController::SearchKey(std::string name)
//{
//    Json::Value root;
//    Json::Value searchs;
//    root["request"] = "SEARCH";

//    std::vector<Film *> film = m_movieAndTelevisionBroker->SearchFilm(name);
//    std::vector<Drame *> drame = m_movieAndTelevisionBroker->SearchDrama(name);
//    std::vector<Comic *> comic = m_movieAndTelevisionBroker->SearchComic(name);
//    std::vector<Actor *> actor = m_movieAndTelevisionBroker->SearchActor(name);
//    std::vector<Director *> director = m_movieAndTelevisionBroker->SearchDirector(name);


//    if(film.size() != 0)
//    {
//        Json::Value search;
//        std::vector<std::string> searchInfo;
//        film[0]->searchInfo(searchInfo);
//        search["type"] = "Film";
//        search["name"] = searchInfo[0];
//        search["post"] = searchInfo[1];
//        search["introduction"] = searchInfo[2];
////        search["episode"] = searchInfo[3];
//        searchs.append(search);
//    }
//    else if(drame.size() != 0){
//        Json::Value search;
//        std::vector<std::string> searchInfo;
//        drame[0]->searchInfo(searchInfo);
//        search["type"] = "Drama";
//        search["name"] = searchInfo[0];
//        search["post"] = searchInfo[1];
//        search["introduction"] = searchInfo[2];
//        search["episode"] = searchInfo[3];
//        searchs.append(search);
//    }
//    else if (comic.size() != 0) {
//        Json::Value search;
//        std::vector<std::string> searchInfo;
//        comic[0]->searchInfo(searchInfo);
//        search["type"] = "Comic";
//        search["name"] = searchInfo[0];
//        search["post"] = searchInfo[1];
//        search["introduction"] = searchInfo[2];
//        search["episode"] = searchInfo[3];
//        searchs.append(search);
//    }
//    else if(actor.size() != 0)
//    {
//        Json::Value search;
//        std::vector<std::string> searchInfo;
//        actor[0]->searchInfo(searchInfo);
//        search["type"] = "Actor";
//        search["name"] = searchInfo[0];
//        search["birthday"] = searchInfo[1];
//        search["introduction"] = searchInfo[2];
//        search["photo"] = searchInfo[3];
//        search["region"] = searchInfo[4];
//        searchs.append(search);
//    }
//    else if(director.size() != 0){
//        Json::Value search;
//        std::vector<std::string> searchInfo;
//        director[0]->searchInfo(searchInfo);
//        search["type"] = "Director";
//        search["name"] = searchInfo[0];
//        search["birthday"] = searchInfo[1];
//        search["introduction"] = searchInfo[2];
//        search["photo"] = searchInfo[3];
//        search["region"] = searchInfo[4];
//        searchs.append(search);
//    }
//    else{
//        Json::Value search;
//        search["type"] = "None";
//        searchs.append(search);
//    }
//    root["searchResult"] = searchs;
//    std::string out = root.toStyledString();
//    std::cout << "aaa" << out << std::endl;
//    return out;
//}

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
        std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

        item["rtspURL"] = url;
        arryObj.append(item);
    }
    root["movieAndTelevision"] = arryObj;
    std::string out = root.toStyledString();

    return out;
}

std::string BrowseAndWatchController::varietyInterface(int type)
{
    VarietyType varietytype;
    switch(type) {
    case 0:
        varietytype = VarietyType::Recommend;
        break;
    case 1:
        varietytype = VarietyType::RealityShow;
        break;
    case 2:
        varietytype = VarietyType::TalentShow;
        break;
    case 3:
        varietytype = VarietyType::Food;
        break;
    case 4:
        varietytype = VarietyType::Travel;
        break;
    case 5:
        varietytype = VarietyType::ActualRecord;
        break;
    case 6:
        varietytype = VarietyType::Funny;
        break;
    case 7:
        varietytype = VarietyType::Interview;
        break;
    }

    std::vector<Variety> varieties;
    varieties = m_movieAndTelevisionBroker->getVarieties(varietytype);

    Json::Value root;
    Json::Value arryObj;
    root["request"] = "INTERFACE";
    root["interface"] = 4;
    root["type"] = type;
    for(int i=0;i != varieties.size();i++){
        std::vector<std::string> resource;
        resource = varieties[i].show(false);
        Json::Value item;
        item["name"] = resource[0];
        item["post"] = resource[1];
        std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
        item["rtspURL"] = url;
        arryObj.append(item);
    }
    root["movieAndTelevision"] = arryObj;
    std::string out = root.toStyledString();

    return out;
}

std::string BrowseAndWatchController::drameInterface(int type)
{
    DrameType drametype;
    switch(type) {
    case 0:
        drametype = DrameType::Recommend;
        break;
    case 1:
        drametype = DrameType::AncientCostume;
        break;
    case 2:
        drametype = DrameType::Suspense;
        break;
    case 3:
        drametype = DrameType::MartialArts;
        break;
    case 4:
        drametype = DrameType::Metropolis;
        break;
    case 5:
        drametype = DrameType::History;
        break;
    case 6:
        drametype = DrameType::Idol;
        break;
    case 7:
        drametype = DrameType::Family;
        break;
    case 8:
        drametype = DrameType::ScienceFiction;
        break;
    }

    std::vector<Drame> drames; color: "lightblue";
    drames = m_movieAndTelevisionBroker->getDrames(drametype);

    Json::Value root;
    Json::Value arryObj;
    root["request"] = "INTERFACE";
    root["interface"] = 2;
    root["type"] = type;
    for(int i=0;i != drames.size();i++){
        std::vector<std::string> resource;
        resource = drames[i].show(false);
        Json::Value item;
        item["name"] = resource[0];
        item["post"] = resource[1];
        std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
        item["rtspURL"] = url;
        arryObj.append(item);
    }
    root["movieAndTelevision"] = arryObj;
    std::string out = root.toStyledString();

    return out;
}

std::string BrowseAndWatchController::comicInterface(int type)
{
    ComicType comictype;
    switch(type){
    case 1:
        comictype =ComicType::RobotWars;
        break;
    case 2:
        comictype = ComicType::Youth;
        break;
    case 3:
        comictype = ComicType::Combat;
        break;
    case 4:
        comictype = ComicType::Love;
        break;
    case 5:
        comictype = ComicType::Kayoing;
        break;
    case 6:
        comictype = ComicType::WarmBlood;
        break;
    case 7:
        comictype = ComicType::Campus;
        break;
    default:
        break;
    }
    std::vector<Comic> comics;
    comics = m_movieAndTelevisionBroker->getComics(comictype);

    Json::Value root;
    Json::Value arryObj;
    root["request"] = "INTERFACE";
    root["interface"] = 3;
    root["type"] = type;

    for(int i = 0; i != comics.size();i++)
    {
        std::vector<std::string> resource;
        resource = comics[i].show(false);
        Json::Value item;
        item["name"] = resource[0];
        item["post"] = resource[1];

        std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

        item["rtspURL"] = url;
        arryObj.append(item);
    }
    root["movieAndTelevision"] = arryObj;
    std::string out = root.toStyledString();

    return out;
}

bool BrowseAndWatchController::addBrowseRecord(std::string recordName, std::string startTime, std::string duration, std::string type)
{
    if(m_movieAndTelevisionBroker->addBrowseRecord(recordName, startTime, duration, type)
            == true){
        return true;
    } else {
        return false;
    }
}

std::string BrowseAndWatchController::getBrowseRecord()
{
    return m_movieAndTelevisionBroker->getBrowseRecord();
}

std::string BrowseAndWatchController::getUrl(std::string name)
{
    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + name;
    return url;
}
