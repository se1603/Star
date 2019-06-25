//董梦丹 4-21
//最后修改于 4-28
#ifndef COLLECTION_H
#define COLLECTION_H
#include <QObject>

class Audience;
class MovieAndTelevision;
class Collection
{
public:
    Collection();
private:
    QString m_collectTime;

    Audience* m_audience;
    MovieAndTelevision* m_movieAndTelevision;
};

#endif // COLLECTION_H
