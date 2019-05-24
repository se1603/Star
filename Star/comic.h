#ifndef COMIC_H
#define COMIC_H

#include "movieandtelevision.h"

enum class ComicType{
    RobotWars = 1,  //机战
    Youth = 2,      //青春
    Combat = 3,     //格斗
    Love = 4,       //恋爱
    Kayoing = 5,    //美少女
    WarmBlood = 6,  //热血
    Campus  = 7     //校园
};

class Comic:public MovieAndTelevision
{
public:
    Comic(std::string name,std::string introduction,
          Region region,std::vector<std::string> posts,
          std::vector<std::string> actors,
          std::vector<std::string> directors,std::vector<ComicType> types,int episode,std::vector<int> recommends);


    std::vector<std::string> show(bool recommend);  //动漫显示的消息
    void findComicByType(ComicType type, std::vector<Comic> &comics);  //获取该类动漫
    void findComicByRecommend(int recommend,std::vector<Comic> &comics); //获取该类推荐下的动漫
private:
    std::vector<ComicType> m_type;
};


#endif // COMIC_H
