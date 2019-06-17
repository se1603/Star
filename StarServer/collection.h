#ifndef COLLECTION_H
#define COLLECTION_H
#include <iostream>
#include <string>

class Audience;
class MovieAndTelevision;
class Collection
{
    friend class Audience;
public:
    Collection(std::string collecttime,Audience* a,MovieAndTelevision* m);
private:
    std::string m_collectionTime;

    Audience* m_audience;
    MovieAndTelevision* m_movieAndTelevision;
};

#endif // COLLECTION_H
