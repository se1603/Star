#ifndef RTSPRTPDEFINE_H
#define RTSPRTPDEFINE_H

#include <stdint.h>
#include "threadpool.h"

struct RtpTcpHeader
{
    int8_t	dollar;
    int8_t	channel;
    int16_t	len;
};

struct RtpHeader
{
    /* byte 0 */
    uint8_t csrcLen: 4;  			// CSRC count
    uint8_t extension: 1;   			// header extend
    uint8_t padding: 1;   			// padding flag
    uint8_t version : 2;		// version

    /* byte 1 */
    uint8_t payloadType: 7;		// payload type
    uint8_t marker: 1;				// mark bit

    /* bytes 2,3 */
    uint16_t seq;				// sequence number;
    /* bytes 4-7 */
    uint32_t timestamp;				// timestamp
    /* bytes 8-11 */
    uint32_t ssrc;				// sync source
};

typedef enum{
    RTSP_OPTIONS = 0,
    RTSP_DESCRIBE = 1,
    RTSP_SETUP = 2,
    RTSP_PLAY = 3,
    RTSP_PAUSE = 4,
    RTSP_TEARDOWN = 5,
    RTSP_SET_PARAMETER = 6,
    RTSP_GET_PARAMETER = 7,
    RTSP_METHOD_MAX
}RtspMethod;

struct RtspMethodStr{
    int method;
    const char* method_str;
};

extern const RtspMethodStr methods[RTSP_METHOD_MAX];

struct RtspCode{
    int code;
    const char* code_str;
};

extern const RtspCode codes[15];

#endif // RTSPRTPDEFINE_H
