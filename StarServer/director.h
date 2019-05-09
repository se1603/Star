/* Author:王梦娟
 * Date:2019-4-26
 * Note:导演
*/
#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <string>
#include "region.h"

class Director
{
public:
    Director();

private:
    std::string m_name;
    std::string m_birthday;
    Region m_region;
    std::string m_introduction;
};

#endif // DIRECTOR_H
