#include "tsparse.h"
#include <netinet/in.h>

TsParse::TsParse()
{

}

TsParse::~TsParse()
{

}

int TsParse::getPcr(const uint8_t *data, uint64_t &pcr)
{
    TSHeader *tsh = (TSHeader*)data;
    if(tsh->sync != 0x47 || tsh->field_control < 2 || tsh->field_len < 1 || tsh->pcr == 0)
        return -1;
    TSPcr* pcr_info = (TSPcr*)(data + sizeof (TSHeader));
    pcr = ntohl(pcr_info->pcr_base);
    pcr = pcr << 1 | pcr_info->pcr_basebit;
    pcr = pcr * 300 + pcr_info->pcr_ext;
    pcr /= 300;
    return 0;
}

bool TsParse::isUnitStart(const uint8_t *data)
{
    TSHeader* tsh = (TSHeader *)data;
    return tsh->sync == 0x47 && tsh->unit_start == 1 ? true : false;
}
