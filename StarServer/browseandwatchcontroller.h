#ifndef BROWSEANDWATCHCONTROLLER_H
#define BROWSEANDWATCHCONTROLLER_H

#include "controller.h"
#include "movieandtelevisionbroker.h"

class BrowseAndWatchController : public Controller
{
public:
    static std::shared_ptr<BrowseAndWatchController> getInstance()
    {
        return m_instance;
    }

    std::map<std::string, std::vector<MovieAndTelevision>> getAllMovieAndTeleVision();

    std::string interface(int category,int type);  //电影 武侠
    std::string category(int type);   //目录

    std::string filmInterface(int type); //武侠

private:
    BrowseAndWatchController();
    static std::shared_ptr<BrowseAndWatchController> m_instance;
    std::shared_ptr<MovieAndTelevisionBroker> m_movieAndTelevisionBroker;
};

#endif // BROWSEANDWATCHCONTROLLER_H
