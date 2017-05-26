/******************************************************************************
** Copyright (C) 2017 Sony Corporation

******************************************************************************/
#ifndef __NET_SERVER_SERVICE_HANDLER_GET_TC_H__
#define __NET_SERVER_SERVICE_HANDLER_GET_TC_H__

#include "service_handler.h"

namespace NetServer{

class ServiceHandlerGetTc: public ServiceHandler{
public:
    ServiceHandlerGetTc();
    virtual ~ServiceHandlerGetTc();
    virtual void doRequest(Data_Transfer& param);

private:
    void parseData(Data_Parse& out, std::string str);
};

}

#endif

