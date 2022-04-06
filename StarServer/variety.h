#ifndef VARIETY_H
#define VARIETY_H
#include "movieandtelevision.h"

enum class VarietyType {
    Recommend = 0,
    RealityShow = 1,
    TalentShow = 2,
    Food = 3,
    Travel = 4,
    ActualRecord = 5,
    Funny = 6,
    Interview = 7
};

class Variety : public MovieAndTelevision
{
public:
    Variety(std::string name,std::string introduction,
            Region region,std::vector<std::string> posts,
            std::vector<Actor *> actors,
            std::vector<Director *> directors,std::vector<VarietyType> types,
            std::vector<int> recommends,int episodes);

    Variety(){}

    std::vector<std::string> show(bool recommend);
    void findVarietyByType(VarietyType type,std::vector<Variety> &varieties);
    void findVarietyByRecommend(int recommend,std::vector<Variety> &varieties);

    void recodeInfo(std::string name,std::vector<std::string> &v);
    bool findByName(std::string name);

    void getActorInfo(std::string name,std::vector<std::string> &v);
    void save(std::map<std::string,Variety> &varietys);
private:
    std::vector<VarietyType> m_type;
};
#endif // VARIETY_H
