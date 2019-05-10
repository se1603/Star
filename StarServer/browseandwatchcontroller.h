/* Author:王梦娟
 * Date:2019-4-25 控制器，应用逻辑层。
 * Date:2019-5-8  去掉实体类的get set函数
*/
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

    std::string interface(int category,int type);  //每个目录下的界面显示
    std::string category(int type);   //目录信息
    std::string recommend(int category);   //每个目录下的推荐页面

    std::string filmInterface(int type); //电影界面显示信息

    //综艺界面显示信息
    std::string varietyInterface(int type);
private:
    BrowseAndWatchController();
    static std::shared_ptr<BrowseAndWatchController> m_instance;
    std::shared_ptr<MovieAndTelevisionBroker> m_movieAndTelevisionBroker;
};

#endif // BROWSEANDWATCHCONTROLLER_H
