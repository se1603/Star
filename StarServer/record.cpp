#include "record.h"
#include "movieandtelevision.h"

Record::Record(std::string startPlayTime, std::string duration, Audience *a, MovieAndTelevision *m)
{
    m_startPlayTime = startPlayTime;
    m_duration = duration;
    m_audience = a;
    m_movieAndTelevision = m;
}

void Record::showRecord(std::vector<std::string> &a_record)
{
    m_movieAndTelevision->showInfo(a_record);
}

void Record::showAllInfo(std::vector<std::string> &r)
{
    m_movieAndTelevision->showInfo(r);
    r.push_back(m_startPlayTime);
    r.push_back(m_duration);
}

void Record::changeInfo(std::string startTime, std::string duration)
{
    m_startPlayTime = startTime;
    m_duration = duration;
}

bool Record::verifyName(std::string r)
{
    return m_movieAndTelevision->isSame(r);
}
