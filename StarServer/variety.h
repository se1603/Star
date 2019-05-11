//董梦丹 0510
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
            std::vector<std::string> actors,
            std::vector<std::string> directors,std::vector<VarietyType> types,
            std::vector<int> recommends,int episodes);

    std::vector<std::string> show(bool recommend);
    void findVarietyByType(VarietyType type,std::vector<Variety> &varieties);
    void findVarietyByRecommend(int recommend,std::vector<Variety> &varieties);
private:
    std::vector<VarietyType> m_type;
};
#endif // VARIETY_H
