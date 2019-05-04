#ifndef RECORD_H
#define RECORD_H
#include <string>

class Audience;
class MovieAndTelevision;
class Record
{
public:
    Record();
private:
    std::string m_startPlayTime;
    std::string m_duration;

    Audience* m_audience;
    MovieAndTelevision* m_movieAndTelevision;
};

#endif // RECORD_H
