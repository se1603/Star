/*author：古长蓉
 * data：2019-06-24   从movieandtelevisionbroker中分离actorbroker
 */
#ifndef DIRECTORBROKER_H
#define DIRECTORBROKER_H
#include "relationalbroker.h"
#include "director.h"

class DirectorBroker:public RelationalBroker
{
public:
    static DirectorBroker* getInstance(){
        if(m_instance == nullptr)
            m_instance = new DirectorBroker();
        return m_instance;
    }
    ~DirectorBroker();

    void initDirectors();
    Director handleDirector(std::vector<std::string> row);

    std::vector<Director *> findDirector(std::vector<std::string> directors);
    void addMovieAndTelevision(std::vector<std::string> directors, MovieAndTelevision &mat);


    std::vector<Director *> searchDirector(std::string name);

private:
    DirectorBroker();
    static DirectorBroker* m_instance;
    std::map<std::string,Director> m_directors; //导演

};

#endif // DIRECTORBROKER_H
