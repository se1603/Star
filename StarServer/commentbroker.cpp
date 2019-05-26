#include "commentbroker.h"
#include <vector>
#include <iostream>


void CommentBroker::initComment()
{

    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Star",0,NULL,0)){
        std::cout << "In getAudience:Connect MYSQL failed." << std::endl;
    }else{
        std::cout << "In getAudience:Connect MYSQL succeed." << std::endl;
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
                std::cout << i << " " << row[i] << std::endl;
            }
            Comment c = Comment(res[0],row[1]);
            m_comments.insert(std::pair<std::string,Comment>(res[0],c));
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr)
            mysql_close(mysql);
    mysql_library_end();
}

