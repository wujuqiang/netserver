/******************************************************************************
** Copyright (C) 2017 Sony Corporation

******************************************************************************/
#ifndef __NET_SERVER_CRISTIAN_PROCESSOR_H__
#define __NET_SERVER_CRISTIAN_PROCESSOR_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include "processor.h"
#include "common_data.h"
//#include "Util.h"

#ifdef __cplusplus
extern "C"{
#endif	// __cplusplus
//#include <utimer.h>
#ifdef __cplusplus
}
#endif	// __cplusplus

namespace NetServer{

//receive cristian data and handle
class CristianProcessor  : public Processor{
public:
    CristianProcessor();
    virtual ~CristianProcessor();
    virtual void doProcess(Request& req);

private:
    uint64_t getSystemCounts();
    std::string getResponseData(unsigned char* request_data);
};

}

#endif

