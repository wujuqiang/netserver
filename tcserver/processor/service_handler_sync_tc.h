/******************************************************************************
** Copyright (C) 2017 Sony Corporation

******************************************************************************/
#ifndef __NET_SERVER_SERVICE_HANDLER_SYNC_TC_H__
#define __NET_SERVER_SERVICE_HANDLER_SYNC_TC_H__

#include "service_handler.h"

namespace NetServer{

class ServiceHandlerSyncTc: public ServiceHandler{
public:
    ServiceHandlerSyncTc();
    virtual ~ServiceHandlerSyncTc();
    virtual void doRequest(Data_Transfer& param);

private:
    void parseData(Data_Parse& out, std::string str);
    uint8_t checkDataValid(std::string src);
};

}

#endif

