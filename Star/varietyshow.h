//董梦丹 0506
#ifndef VARIETYSHOW_H
#define VARIETYSHOW_H
#include "movieandtelevision.h"

enum class VarietyShowType
{
    Recommend = 0,
    //真人秀
    RealityShow = 1,
    //选秀节目
    TalentShow = 2,
    //美食
    Food = 3,
    //旅游
    Travel = 4,
    //纪实
    Doucumentary = 5,
    //搞笑
    Funny = 6,
    //访谈
    TalkShow = 7
};

class VarietyShow : public MovieAndTelevision
{
public:
    VarietyShow();

    VarietyShowType type() const;
    void setType(int varietyshowtype);

    int episodes() const;
    void setEpisodes(int episodes);
private:
    VarietyShowType m_type;
    int m_episodes;
};

#endif // VARIETYSHOW_H
