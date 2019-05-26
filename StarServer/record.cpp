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
