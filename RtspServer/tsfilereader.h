#ifndef TSFILEREADER_H
#define TSFILEREADER_H

#include "tsparse.h"
#include <stdio.h>

#define TSPKTLEN 188

class TsFileReader
{
public:
    TsFileReader();
    ~TsFileReader();

    int openFile(const char* filename);   //打开文件
    int readFile();   //读取文件
    int getFileRange();   //获取视频时长
    bool seekByTime(uint64_t sec);   //根据时间搜索时间戳
    int getTsPKT(char *buf, int len, uint64_t&pcr);   //获取一个包

private:
    FILE* m_file;
    char m_dataBuff[TSPKTLEN];
    uint64_t m_fileSize;          //文件大小
    uint64_t m_currentPcr;  //当前时间戳
    uint64_t m_startPcr;    //文件起始时间戳
    uint64_t m_lastPcr;     //文件结束时间戳
};

#endif // TSFILEREADER_H
