#ifndef VARIETY_H
#define VARIETY_H
#include "movieandtelevision.h"

enum class VarietyType {
    Recommend = 0,
    RealityShow = 1,
    TalentShow = 2,
    Food = 3,
    Travel = 4,
    ActualRecord = 5,
    Funny = 6,
    Interview = 7
};

class Variety : public MovieAndTelevision
{
public:
    Variety();
};

#endif // VARIETY_H
