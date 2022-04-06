#ifndef TSPARSE_H
#define TSPARSE_H

#include <stdint.h>

typedef struct
{
    uint8_t sync;
    uint8_t pid_high5: 5,
            transport_priority: 1,
            unit_start: 1,
            transport_error: 1;
    uint8_t pid_low8;
    uint8_t counter: 4,
            field_control: 2,
            scrambling_control: 2;
    uint8_t field_len;
    uint8_t field_extension: 1,
            private_data: 1,
            splicing_point: 1,
            opcr: 1,
            pcr: 1,
            stream_priority: 1,
            random_access: 1,
            discontinuity: 1;
}TSHeader;

typedef struct{
    uint32_t pcr_base;
    uint16_t pcr_ext:9,
             reserved:6,
             pcr_basebit:1;
}TSPcr; //时间戳

class TsParse
{
public:
    TsParse();
    ~TsParse();

    static int getPcr(const uint8_t* data, uint64_t& pcr); //获取视频时间戳
    static bool isUnitStart(const uint8_t* data);  //判断是否是音视频单元的开始
};

#endif // TSPARSE_H
