/* Author:王梦娟
 * Date:2019-4-25 控制器，应用逻辑层。
 * Date:2019-5-8  去掉实体类的get set函数
 * author：古长蓉
 * data：2019-06-17  增加搜索关键字函数
*/
#ifndef BROWSEANDWATCHCONTROLLER_H
#define BROWSEANDWATCHCONTROLLER_H

#include "controller.h"
#include "movieandtelevisionbroker.h"

class BrowseAndWatchController : public Controller
{
public:
    static BrowseAndWatchController* getInstance()
    {
        return m_instance;
    }

    ~BrowseAndWatchController();

    std::string interface(int category,int type);  //每个目录下的界面显示
    std::string category(int type);   //目录信息
    std::string recommend(int category);   //每个目录下的推荐页面

    std::string filmInterface(int type); //电影界面显示信息
    std::string drameInterface(int type);//剧集页面显示
    //综艺界面显示信息
    std::string varietyInterface(int type);

    std::string comicInterface(int type);//动漫界面显示信息

    std::string getVideoInfo(std::string name);//获取播放界面中的片库信息
    std::string getActorInfo(std::string name);//获取演员和导演信息

    std::string SearchKey(std::string name); //搜索关键字

    //本地浏览记录
    bool addBrowseRecord(std::string recordName, std::string startTime,
                         std::string duration, std::string type);
    std::string getBrowseRecord();


private:
    BrowseAndWatchController();
    static BrowseAndWatchController* m_instance;
    MovieAndTelevisionBroker* m_movieAndTelevisionBroker;
    std::string m_rtspAddress;
};

#endif // BROWSEANDWATCHCONTROLLER_H
