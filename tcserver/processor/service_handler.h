/******************************************************************************
** Copyright (C) 2017 Sony Corporation

******************************************************************************/
#ifndef __NET_SERVER_SERVICE_HANDLER_H__
#define __NET_SERVER_SERVICE_HANDLER_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <string.h>
#include "common_data.h"

namespace NetServer{

class ServiceHandler{
public:
    ServiceHandler(){}
    virtual ~ServiceHandler(){}
    virtual void doRequest(Data_Transfer& param)=0;
};

}

#endif

