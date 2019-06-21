/*Author:古长蓉
 * date： 2019-06-20 搜索控制器，从浏览影视控制器中分离
 */
#ifndef SEARCHCONTROLLER_H
#define SEARCHCONTROLLER_H
#include <iostream>
#include "controller.h"
#include "movieandtelevisionbroker.h"

class SearchController: public Controller
{
public:
    static SearchController* getInstace()
    {
        return m_instance;
    }

    ~SearchController();
    std::string SearchKeywords(std::string name); //搜索关键字

private:
    SearchController();
    static SearchController* m_instance;
    MovieAndTelevisionBroker* m_movieAndTelevisionBroker;
};

#endif // SEARCHCONTROLLER_H
