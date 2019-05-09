/* Author:王梦娟
 * Date:2019-4-25
 * Note:封装了消息，文件的接收和发送
*/
#include "network.h"
#include <iostream>

//----------------------crc32----------------
static unsigned int crc_table[256];   //256个
static void init_crc_table(void);
static unsigned int crc32(unsigned int crc, unsigned char * buffer, unsigned int size);
/* 第一次传入的值需要固定,如果发送端使用该值计算crc校验码, 那么接收端也同样需要使用该值进行计算 */
unsigned int crc = 0xffffffff;

/* 初始化crc表,生成32位大小的crc表*/
static void init_crc_table(void)
{
    unsigned int c;
    unsigned int i, j;

    for (i = 0; i < 256; i++)
    {
        c = (unsigned int)i;
        for (j = 0; j < 8; j++)
        {
            if (c & 1)
                c = 0xedb88320L ^ (c >> 1);
            else
                c = c >> 1;
        }

        crc_table[i] = c;
    }
}

/* 计算buffer的crc校验码 */
static unsigned int crc32(unsigned int crc,unsigned char *buffer, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++)
    {
        crc = crc_table[(crc ^ buffer[i]) & 0xff] ^ (crc >> 8);
    }

    return crc ;
}

NetWork::NetWork(socket_ptr s)
{
    sock = s;
}

int NetWork::sendto(std::string message, endpoint ep)
{
    boost::asio::ip::udp::endpoint sender_ep;

    Package data;
    bzero(&data,sizeof (data));
    PackageHead pack_info;
    bzero(&pack_info,sizeof (pack_info));

    unsigned int send_index = 0;
    unsigned int receive_index = 0;

    int returnlen = 0;

    try {
        int len = message.length();
        std::cout << len << std::endl;
        if( len > MAXLENGTH)  //长度大于512,分包发送
        {
            char buffer[1024 * 10];
            bzero(buffer,1024 * 10);
            memcpy(buffer,message.data(),sizeof (buffer));
            int readed = 0;
            int count = (len / MAXLENGTH) + 1;
            data.head.count = count;
            while(len){
                memcpy(data.buff,buffer + readed,MAXLENGTH);
                readed += MAXLENGTH;
                len -= MAXLENGTH;
                if(len < 0)
                    len = 0;
                std::cout << "test:" << data.buff << std::endl;
                if(send_index == receive_index){
                    ++send_index;
                    data.head.index = send_index;
                    if(count == 0)
                        data.head.len = sizeof (message) - readed;
                    data.head.len = MAXLENGTH;
                    --count;
                    data.head.crc32val = crc32(crc,(unsigned char *)data.buff,sizeof(data));

                    returnlen = sock->send_to(boost::asio::buffer((char *)&data,sizeof(data)),ep);
                    sock->receive_from(boost::asio::buffer((char *)&pack_info,sizeof(pack_info)),sender_ep);
                    receive_index = pack_info.index;

                    if(pack_info.errorFlag == 1)
                    {
                        pack_info.errorFlag = 0;
                        returnlen = sock->send_to(boost::asio::buffer((char *)&data,sizeof(data)),ep);
                    }
                }
                else {
                    //index不同 重新发送
                    returnlen = sock->send_to(boost::asio::buffer((char *)&data,sizeof(data)),sender_ep);
                    sock->receive_from(boost::asio::buffer((char *)&pack_info,sizeof(pack_info)),sender_ep);
                    receive_index = pack_info.index;
                }
            }
        }
        else { //只需要一个包
            //            std::cout << "leave" << std::endl;
            data.head.count = 1;
            memcpy(data.buff,message.data(),sizeof(data.buff));
            if(send_index == receive_index){
                ++send_index;
                data.head.index = send_index;
                data.head.len = sizeof (message);
                data.head.crc32val = crc32(crc,(unsigned char *)data.buff,sizeof(data));

                returnlen = sock->send_to(boost::asio::buffer((char *)&data,sizeof(data)),ep);

                sock->receive_from(boost::asio::buffer((char *)&pack_info,sizeof(pack_info)),sender_ep);
                std::cout << "leave" << std::endl;
                receive_index = pack_info.index;

                if(pack_info.errorFlag == 1)
                {
                    pack_info.errorFlag = 0;
                    returnlen = sock->send_to(boost::asio::buffer((char *)&data,sizeof(data)),ep);
                }
            }
            else {
                //index不同 重新发送
                returnlen = sock->send_to(boost::asio::buffer((char *)&data,sizeof(data)),sender_ep);
                sock->receive_from(boost::asio::buffer((char *)&pack_info,sizeof(pack_info)),sender_ep);
                receive_index = pack_info.index;
            }
        }

    } catch (boost::system::system_error e) {
        std::cerr << e.what() << std::endl;
    }

    return returnlen;
}

std::string NetWork::receive(boost::asio::ip::udp::endpoint &sender_ep)
{
    Package data;
    bzero(&data,sizeof (data));
    PackageHead pack_info;     //返回给客户端包正确的消息
    bzero(&pack_info,sizeof (pack_info));
    unsigned int crc32value;
    long int id = 1;   //包序列号

    char buffer[1024*10];
    bzero(buffer,sizeof (buffer));   //消息缓存

    //    boost::asio::ip::udp::endpoint sender_ep;

    //检测数据的完整
    std::cout << "WAIT: " << std::endl;
    size_t len = sock->receive_from(boost::asio::buffer(reinterpret_cast<char*>(&data), sizeof(data)),sender_ep);

    int count = data.head.count;
    int read = 0;

    while(count){
        if(len < 0)
            std::cout << "Receive Message From Client failed.\n";
        else {
            crc32value = crc32(crc,(unsigned char *)data.buff,sizeof(data));  //生成校验码
            if(data.head.index == id)
            {
                if(data.head.crc32val == crc32value)
                {
                    pack_info.index = data.head.index;
                    pack_info.len = len;
                    ++id;
                    sock->send_to(boost::asio::buffer((char *)&pack_info,sizeof(pack_info)),sender_ep);
                    memcpy(buffer + read,data.buff,sizeof (data.buff));
                    read += len;
                }
                else {
                    //错误包，重发
                    pack_info.index = data.head.index;
                    pack_info.len = len;
                    pack_info.errorFlag = 1;
                    sock->send_to(boost::asio::buffer((char *)&pack_info,sizeof(pack_info)),sender_ep);
                }
            }
            else if (data.head.index < 0) {//重发包
                pack_info.index = data.head.index;
                pack_info.len = len;
                pack_info.errorFlag = 0;
                sock->send_to(boost::asio::buffer((char *)&pack_info,sizeof(pack_info)),sender_ep);
            }
            else {
                id = 1;
            }
        }
        --count;
    }
    std::string s = buffer;

    return s;
}

long NetWork::sendFile(FILE *fp, endpoint ep)
{
    boost::asio::ip::udp::endpoint sender_ep;
    //发送文件内容
    long int send_id = 0;
    long int receive_id = 0;

    int len = 0; //记录数据长度

    Package data;

    long int total_bytes_read = 0;

    while(true)
    {
        PackageHead head;
        Package data;

        bzero((char *)&data,sizeof(data));

        if(receive_id == send_id)
        {
            ++send_id;

            len = fread(data.buff,sizeof(char),BUFFERSIZE,fp);
            total_bytes_read += len;
            if(len > 0)
            {
                data.head.index = send_id;
                data.head.len = len;
                data.head.crc32val = crc32(crc,(unsigned char *)data.buff,sizeof(data));

                //                std::cout<< "len " << len << std::endl;
                //                std::cout << "crc32: " << data.head.crc32val << std::endl;

                sock->send_to(boost::asio::buffer((char *)&data,sizeof(data)),ep);

                sock->receive_from(boost::asio::buffer((char *)&head,sizeof(head)),sender_ep);
                receive_id = head.index;

                //                std::cout << "receive: " << head.index << std::endl;

                if(head.errorFlag == 1)
                {
                    head.errorFlag = 0;
                    sock->send_to(boost::asio::buffer((char *)&data,sizeof(data)),sender_ep);
                }
            }
            else {
                break;
            }
        }
        else{
            //index不同 重新发送
            sock->send_to(boost::asio::buffer((char *)&data,sizeof(data)),sender_ep);
            sock->receive_from(boost::asio::buffer((char *)&head,sizeof(head)),sender_ep);
            receive_id = head.index;
        }
    }
    bzero((char *)&data,sizeof(data));
    sock->send_to(boost::asio::buffer((char *)&data,0),sender_ep);
    return total_bytes_read;
}
