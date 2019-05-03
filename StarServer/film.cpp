#include "film.h"

Film::Film()
{

}

FilmType Film::type() const
{
    return m_type;
}

void Film::setType(int filmtype)
{
    switch (filmtype) {
    case 1:
        m_type = FilmType::MartialArts;
        break;
    case 2:
        m_type = FilmType::Suspense;
        break;
    case 3:
        m_type = FilmType::Comedy;
        break;
    case 4:
        m_type = FilmType::Action;
        break;
    case 5:
        m_type = FilmType::Love;
        break;
    case 6:
        m_type = FilmType::Cartoon;
        break;
    case 7:
        m_type = FilmType::Terror;
        break;
    case 8:
        m_type = FilmType::ScienceFiction;
        break;
    default:
        break;
    }
}
