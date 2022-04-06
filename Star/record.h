#ifndef RECORD_H
#define RECORD_H
#include <QObject>

class Audience;
class MovieAndTelevision;
class Record
{
public:
    Record();
private:
    QString m_startPlayTime;
    QString m_duration;

    Audience* m_audience;
    MovieAndTelevision* m_movieAndTelevision;
};

#endif // RECORD_H
