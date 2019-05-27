#include "commentbroker.h"
#include <vector>
#include <iostream>
#include "audiencebroker.h"
#include "movieandtelevisionbroker.h"

CommentBroker* CommentBroker::m_instance = new CommentBroker();

void CommentBroker::infoFromDataBase(std::vector<std::string> &v)
{
    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0)){
        std::cout << "In getComment:Connect MYSQL failed." << std::endl;
    }else{
        std::cout << "In getComment:Connect MYSQL succeed." << std::endl;
    }
    std::string sql = "select * from Comment";
    if(mysql_query(mysql,sql.data())){
        std::cout << "Comment 获取失败"<< std::endl;
    }else{
        result = mysql_use_result(mysql);//获取结果集
        while(1){
            row = mysql_fetch_row(result);
            if(row == nullptr) break;
            std::vector<std::string> res;
            for(unsigned i = 0; i < mysql_num_fields(result);++i){
                res.push_back(row[i]);
                v.push_back(row[i]);
//                std::cout << i << " " << row[i] << std::endl;
            }
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr)
            mysql_close(mysql);
    mysql_library_end();
}

bool CommentBroker::insertComment(std::string an, std::string mn, std::string t, std::string c)
{
    MYSQL* mysql;
    mysql = new MYSQL;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0)){
        std::cout << "Comment connect failed" << std::endl;
    }else{
        std::cout << "Comment connect Successed" << std::endl;
    }

    std::cout << "insert comment" << t << std::endl;
    std::string sql = "insert into Comment(audienceName,name,comment,time) values('"+an+"','"+mn+"','"+c+"','"+t+"');";
    if(mysql_query(mysql,sql.data())){
        std::cout <<"insert failed"<< std::endl;
        return false;
    }else{
        return true;
    }
//    if(mysql != nullptr){
//        mysql_close(mysql);
    //    }
}


void CommentBroker::initcomment(std::string n, std::string c,std::string t, Audience *a, MovieAndTelevision* m)
{
    Comment c1 = Comment(t,c,a,m);
    std::cout << "initcomment time" << t << std::endl;
    m_comments.insert(std::pair<std::string,Comment>(n,c1));
}

bool CommentBroker::CommentSize()
{
    std::cout << m_comments.size()<< std::endl;
    if(m_comments.size() != 0)
        return true;
    else
        return false;
}

void CommentBroker::getCommentInfo(std::string name,std::vector<std::string> &v)
{
//    std::vector<std::string> vec;
    auto c = m_comments.find(name);
    if(c != m_comments.end()){
        for(int i = 0; i != m_comments.count(name);i++,c++){
           c->second.getCommentInfo(v);
        }
    }
}

void CommentBroker::goodCommentInfo(std::string name, std::vector<std::string> &v)
{
    auto c = m_comments.find(name);
    if(c != m_comments.end()){
        for(int i = 0;i != m_comments.count(name);i++,c++){
            if(c->second.commentSize()==true){
                c->second.getCommentInfo(v);
            }
        }
    }
}

CommentBroker::CommentBroker()
{

}
