/******************************************************************************
** Copyright (C) 2017 Sony Corporation

******************************************************************************/
#ifndef __NET_SERVER_TC_PROCESSOR_H__
#define __NET_SERVER_TC_PROCESSOR_H__

#include "processor.h"
#include "common_data.h"

namespace NetServer{

//receive tc data and handle
class TcProcessor  : public Processor{
public:
    TcProcessor();
    virtual ~TcProcessor();
    virtual void doProcess(Request& req);
    virtual Error_Code doResponse(Data_Transfer& param);
};

}

#endif

