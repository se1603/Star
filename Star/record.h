//董梦丹 4-21
//最后修改于 4-28
#ifndef RECORD_H
#define RECORD_H
#include <QObject>

class Audience;
class MovieAndTelevision;
class Record : public QObject
{
    Q_OBJECT
public:
    Record();
private:
    QString m_startPlayTime;
    QString m_duration;

    Audience* m_audience;
    MovieAndTelevision* m_movieAndTelevision;
};

#endif // RECORD_H
