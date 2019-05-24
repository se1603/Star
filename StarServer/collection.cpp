#include "collection.h"

Collection::Collection(std::string collecttime, Audience *a, MovieAndTelevision *m)
{
    m_collectionTime = collecttime;
    m_audience = a;
    m_movieAndTelevision = m;
}
