/*create database Star;
 *
 *create table MovieAndTelevision(type varchar(30) NOT NULL,classification varchar(200));
 *
 * insert into MovieAndTelevision(type,classification) values('电影','武侠，悬疑，喜剧，动作，爱情，卡通，惊悚，科幻');
 *
 * create table Film(name varchar(30) NOT NULL,type int NOT NULL,region int NOT NULL,director varchar(20),actor varchar(50),post varchar(100),introduction varchar(500),recommend int NOT NULL);
 *
 * insert into Film(name,type,region,director,actor,post,introduction,recommend) values('大圣归来','6','1','田晓鹏','张磊','./StarServer/post/films/daShengGuiLai.jpg','五百年前，由石猴变化而成的齐天大圣孙悟空（张磊 配音）大闹天宫，最终被如来佛祖镇压在了五行山下。此去经年，长安城内突然遭到山妖洗劫，童男童女哭声连连，命悬一线。危机时刻，自幼被行脚僧法明（吴文伦 配音）抚养长大的江流儿（林子杰 配音）救下了一个小女孩，结果反遭山妖追杀。','1');
 * insert into Film(name,type,region,director,actor,post,introduction,recommend) values('大鱼海棠','6','1','梁旋','季冠霖','./StarServer/post/films/daYuHaiTang.jpg','所有活着的人类，都是海里一条巨大的鱼，出生的时候他们从海的此岸出发。他们的生命就像横越大海，有时相遇，有时分开……死的时候，他们便到了岸，各去各的世界。四十五亿年前，这个星球上，只有一片汪洋大海，和一群古老的大鱼。','3');
 *
 * insert into Film(name,type,director,region) values('毒液：致命守护者','8','鲁本.弗雷斯彻','2');
 * insert into Film(name,type,director,region) values('黑豹','8','查德维克.博斯曼','2');
 * insert into Film(name,type,director,region) values('了不起的盖茨比','5','巴兹.鲁赫曼','2');
 * insert into Film(name,type,director,region) values('怦然心动','5','罗伯.莱纳','2');
*/

#include "relationalbroker.h"

RelationalBroker::RelationalBroker()
{

}

/*create table Film(name varchar(30) NOT NULL,type varchar(30) NOT NULL,region varchar(30) NOT NULL);
 * insert into Film(name,type,region) values('大圣归来','动画','中国');
 *
 *  MartialArts = 1,    //武侠
    Suspense = 2,       //悬疑
    Comedy = 3,         //喜剧
    Action = 4,         //动作
    Love = 5,           //爱情
    Cartoon = 6,        //动画
    Terror = 7,         //惊悚
    ScienceFiction = 8  //科幻

    China = 1,
    American = 2,
    Korea = 3,
    India = 4,
    THailand = 5,
    Britain = 6

    主页推荐 1
    新片 2
    动画电影推荐 3
    爱情电影推荐 4
    喜剧电影推荐 5

*/
