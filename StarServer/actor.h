/* Author:王梦娟
 * Date:2019-4-25
 * Note:演员
*/
#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include "region.h"

class Actor
{
public:
    Actor();

private:
    std::string m_name;        //名字
    std::string m_birthday;    //生日
    Region m_region;           //地区
    std::string m_introduction;  //简介
};

#endif // ACTOR_H
