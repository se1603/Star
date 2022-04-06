#include "tsfilereader.h"

TsFileReader::TsFileReader()
{
    m_file = NULL;
    m_fileSize = 0;
    m_startPcr = -1;
    m_lastPcr = -1;
    m_currentPcr = -1;
}

TsFileReader::~TsFileReader()
{
    if(m_file != NULL)
    {
        fclose(m_file);
        m_file = NULL;
    }
}

int TsFileReader::openFile(const char *filename)
{
    if(m_file != NULL)
    {
        fclose(m_file);
        m_file = NULL;
    }
    m_file = fopen64(filename, "rb");
    if(m_file == NULL)
    {
        printf("Open %s file failed.\n",filename);
        return -1;
    }

    if(readFile() < 0)
        return -1;

    printf("Open success! File size: %lld, start pcr:%lld, last pcr:%lld\n",
           m_fileSize,m_startPcr,m_lastPcr);
    return 0;
}

int TsFileReader::readFile()
{
    m_fileSize = 0;
    m_startPcr = -1;
    m_lastPcr = -1;
    m_currentPcr = -1;

    //设置文件指针位置
    if(fseeko64(m_file, 0, SEEK_END) != 0)
    {
        printf("Seek to end failed.\n");
        return -1;
    }

    m_fileSize = ftello64(m_file);
    if(m_fileSize < TSPKTLEN)
    {
        printf("File is too small,size: %ld\n.",m_fileSize);
        return -1;
    }

    if(fseeko64(m_file,0,SEEK_SET) != 0)
    {
        printf("Seek to begin failed.\n");
        return -1;
    }

    //文件偏移量
    int64_t offset = -1;
    while(1)
    {
        if(offset >= 0)
        {
            if(fseeko64(m_file, offset, SEEK_SET) == -1)
            {
                printf("Seek file to %lld failed.\n", offset);
                return -1;
            }
        }
        uint8_t buffer[TSPKTLEN];
        if(fread(buffer, sizeof (uint8_t), TSPKTLEN, m_file) != TSPKTLEN)
        {
            printf("Read first ts PKT failed.\n");
            return -1;
        }

        uint64_t pcr = 0;
        if(TsParse::getPcr(buffer,pcr) < 0)
        {
            if(offset != -1)
                offset -= TSPKTLEN;
            continue;
        }
        if(m_startPcr == (uint64_t) - 1)
        {
            m_currentPcr = m_startPcr = pcr;
            offset = (m_fileSize / TSPKTLEN - 1) * TSPKTLEN;
        }
        else
        {
            m_lastPcr = pcr;
            break;
        }
    }

    if(m_lastPcr <= m_startPcr)
    {
        printf("Get file Range failde.\n");
        return -1;
    }
    if(fseeko64(m_file,0,SEEK_SET) != 0)
    {
        printf("Seek to end failed.\n");
        return -1;
    }
    return 0;
}

int TsFileReader::getFileRange()
{
    return int((m_lastPcr - m_startPcr) / 90000);
}

bool TsFileReader::seekByTime(uint64_t sec)
{
    int64_t diff_sec = (int64_t)( m_startPcr + sec*1000 - m_currentPcr );
    if( diff_sec < 2000 && diff_sec > -2000 )
        return true;
    int64_t offset = m_fileSize/((m_lastPcr-m_startPcr)/90000)*sec/TSPKTLEN*TSPKTLEN;
    if( offset > (int64_t)m_fileSize )
        offset = m_fileSize;
    if( fseeko64( m_file, offset, SEEK_SET ) != 0 ){
        printf("Seek to end failed\n" );
        return false;
    }
    return true;
}

int TsFileReader::getTsPKT(char *buf, int len, uint64_t &pcr)
{
    int ret = fread( buf, sizeof(char), len, m_file );
    if( ret < TSPKTLEN ){
        printf("Read ts pkts failed\n" );
        return -1;
    }

    uint64_t cur_pcr = -1;
    for( int i = 0; i < ret/TSPKTLEN; i++ )
        TsParse::getPcr( (const uint8_t*)buf+i*TSPKTLEN, cur_pcr );
    if( cur_pcr != (uint64_t)-1 )
        m_currentPcr = cur_pcr;
    pcr = m_currentPcr;
    return ret;
}
