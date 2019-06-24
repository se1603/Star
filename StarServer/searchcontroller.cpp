/*Author:古长蓉
 * date： 2019-06-20 搜索控制器，从浏览影视控制器中分离
 */
#include "json/json.h"
#include "film.h"
#include "variety.h"
#include "drame.h"
#include "comic.h"
#include "searchcontroller.h"


SearchController* SearchController::m_instance = new SearchController();

SearchController::SearchController(){
    m_actorbroker = ActorBroker::getInstance();
    m_directorbroker = DirectorBroker::getInstance();
    m_movieAndTelevisionBroker = MovieAndTelevisionBroker::getInstance();
    m_browseAndWatchController = BrowseAndWatchController::getInstance();
}

SearchController::~SearchController()
{
    delete m_instance;
}

std::string SearchController::searchKeywords(std::string name)
{
    Json::Value root;
    Json::Value searchs;
    root["request"] = "SEARCH";

    std::vector<Film *> film = m_movieAndTelevisionBroker->searchFilm(name);
    std::vector<Drame *> drame = m_movieAndTelevisionBroker->searchDrama(name);
    std::vector<Comic *> comic = m_movieAndTelevisionBroker->searchComic(name);
    std::vector<Actor *> actor = m_actorbroker->searchActor(name);
    std::vector<Director *> director = m_directorbroker->searchDirector(name);


    if(film.size() != 0)
    {
        Json::Value search;
        std::vector<std::string> searchInfo;
        film[0]->searchInfo(searchInfo);
        search["type"] = "Film";
        search["name"] = searchInfo[0];
        search["post"] = searchInfo[1];
        search["introduction"] = searchInfo[2];
        search["rtspURL"] = m_browseAndWatchController->getUrl(searchInfo[0]);
//        search["episode"] = searchInfo[3];
        searchs.append(search);
    }
    else if(drame.size() != 0){
        Json::Value search;
        std::vector<std::string> searchInfo;
        drame[0]->searchInfo(searchInfo);
        search["type"] = "Drama";
        search["name"] = searchInfo[0];
        search["post"] = searchInfo[1];
        search["introduction"] = searchInfo[2];
        search["rtspURL"] = m_browseAndWatchController->getUrl(searchInfo[0]);
        search["episode"] = searchInfo[3];
        searchs.append(search);
    }
    else if (comic.size() != 0) {
        Json::Value search;
        std::vector<std::string> searchInfo;
        comic[0]->searchInfo(searchInfo);
        search["type"] = "Comic";
        search["name"] = searchInfo[0];
        search["post"] = searchInfo[1];
        search["introduction"] = searchInfo[2];
        search["rtspURL"] = m_browseAndWatchController->getUrl(searchInfo[0]);
        search["episode"] = searchInfo[3];
        searchs.append(search);
    }
    else if(actor.size() != 0)
    {
        Json::Value search;
        std::vector<std::string> searchInfo;
        actor[0]->searchInfo(searchInfo);
        search["type"] = "Actor";
        search["name"] = searchInfo[0];
        search["birthday"] = searchInfo[1];
        search["introduction"] = searchInfo[2];
        search["photo"] = searchInfo[3];
        search["region"] = searchInfo[4];
        searchs.append(search);
    }
    else if(director.size() != 0){
        Json::Value search;
        std::vector<std::string> searchInfo;
        director[0]->searchInfo(searchInfo);
        search["type"] = "Director";
        search["name"] = searchInfo[0];
        search["birthday"] = searchInfo[1];
        search["introduction"] = searchInfo[2];
        search["photo"] = searchInfo[3];
        search["region"] = searchInfo[4];
        searchs.append(search);
    }
    else{
        Json::Value search;
        search["type"] = "None";
        searchs.append(search);
    }
    root["searchResult"] = searchs;
    std::string out = root.toStyledString();
    std::cout << "aaa" << out << std::endl;
    return out;
}
