#include "service_handler_get_tc.h"
#include "string.h"
#include "parse.h"
#include "response.h"
#include "dummy_service.h"
#include "tc_processor.h"

namespace NetServer{

ServiceHandlerGetTc::ServiceHandlerGetTc()
{

}

ServiceHandlerGetTc::~ServiceHandlerGetTc()
{
    
}

void ServiceHandlerGetTc::doRequest(Data_Transfer& param)
{

    Data_Parse data_parse;
    memset(&data_parse,0,sizeof(data_parse));
    parseData(data_parse, param.data);

    TC_LOG_DBG("offset:%ld", data_parse.param.get_data.offset);

    Parse parse(data_parse);

    TcProcessor tc_processor;

    Response response(param.ip, tc_processor);

    DummyService dummy_service;
    dummy_service.handler(parse, response);

}

void ServiceHandlerGetTc::parseData(Data_Parse& out, std::string src)
{
    TC_LOG_DBG("ParseData.data is (%s)", src.c_str());

    out.type = REQ_TYPE_GET_TC;
    out.param.get_data.offset = (int64_t)strtol(src.c_str(), NULL, TRANSFER_DATA_DECIMAL);

}


}

