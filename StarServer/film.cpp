#include "film.h"

Film::Film()
{

}

std::vector<FilmType> Film::type() const
{
    return m_type;
}

void Film::setType(int filmtype)
{
    switch (filmtype) {
    case 1:
        m_type.push_back(FilmType::MartialArts);
        break;
    case 2:
        m_type.push_back(FilmType::Suspense);
        break;
    case 3:
        m_type.push_back(FilmType::Comedy);
        break;
    case 4:
        m_type.push_back(FilmType::Action);
        break;
    case 5:
        m_type.push_back(FilmType::Love);
        break;
    case 6:
        m_type.push_back(FilmType::Cartoon);
        break;
    case 7:
        m_type.push_back(FilmType::Terror);
        break;
    case 8:
        m_type.push_back(FilmType::ScienceFiction);
        break;
    default:
        break;
    }
}
