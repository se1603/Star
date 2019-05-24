/*Author:古长蓉
 * Data:2019-5-12
 * Note:剧集（drame）
 */
#ifndef DRAME_H
#define DRAME_H

#include "movieandtelevision.h"

enum class DrameType
{
    Recommend = 0,
    AncientCostume = 1,   //古装
    Suspense = 2,     //悬疑
    MartialArts = 3,     //武侠
    Metropolis = 4,     //都市
    History = 5,     //历史
    Idol = 6,       //偶像
    Family = 7,       //家庭
    ScienceFiction = 8      //科幻
};

class Drame : public MovieAndTelevision
{
public:
    Drame(std::string name,std::string introduction,
          Region region,std::vector<std::string> posts,
          std::vector<Actor *> actors,
          std::vector<Director *> directors,
          std::vector<DrameType> types,int episode,std::vector<int> recommends);
    Drame(){}
    std::vector<std::string> show(bool recommend);
    void findDrameByType(DrameType type, std::vector<Drame> &drames);
    void findDrameByRecommend(int recommend, std::vector<Drame> &drames);
    bool findByName(std::string name);

    void recodeInfo(std::string name,std::vector<std::string> &v);

    void getActorInfo(std::string name,std::vector<std::string> &v);
    void save(std::map<std::string,Drame> &drames);
private:
    std::vector<DrameType> m_type;
};

#endif // DRAME_H
