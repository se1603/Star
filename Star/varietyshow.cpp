#include "varietyshow.h"

VarietyShow::VarietyShow()
{

}

VarietyShowType VarietyShow::type() const
{
    return m_type;
}

void VarietyShow::setType(int varietyshowtype)
{
    switch (varietyshowtype) {
    case 1:
        m_type = VarietyShowType::RealityShow;
        break;
    case 2:
        m_type = VarietyShowType::TalentShow;
        break;
    case 3:
        m_type = VarietyShowType::Food;
        break;
    case 4:
        m_type = VarietyShowType::Travel;
        break;
    case 5:
        m_type = VarietyShowType::Doucumentary;
        break;
    case 6:
        m_type = VarietyShowType::Funny;
        break;
    case 7:
        m_type = VarietyShowType::TalkShow;
        break;
    default:
        break;
    }
}

int VarietyShow::episodes() const
{
    return m_episodes;
}

void VarietyShow::setEpisodes(int episodes)
{
    m_episodes = episodes;
}
