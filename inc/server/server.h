#ifndef _SERVER_DEFINED_FUCK_
#define _SERVER_DEFINED_FUCK_

#include <headers.h>

enum DATA_REQUEST_TYPE
{
DATA_REQUEST_STATE,
DATA_REQUEST_READY,
};

struct data_request_t
{
uint32_t request_type;
};

#endif