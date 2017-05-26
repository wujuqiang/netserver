#include "dummy_service.h"
#include "string.h"

namespace NetServer {

DummyService::DummyService()
{

}

DummyService::~DummyService()
{
    
}

void DummyService::handler(Parse data, Response response)
{
    Data_Parse data_parse = data.getParseData();

    char res_data[BUFF_READ_MAX_LEN] = {'\0'};
    if(REQ_TYPE_SYNC_TC == data_parse.type){
        res_data[0] = RES_TYPE_SYNC_TC;
        res_data[1] = '0';
        res_data[2] = strnlen("192.168.0.102", 256);
        strncpy(&res_data[3], "192.168.0.102", strnlen("192.168.0.102", 256)+1);
    }else if(REQ_TYPE_GET_TC == data_parse.type){
        res_data[0] = RES_TYPE_GET_TC;
        res_data[1] = strnlen("9876543210000T11:22:33:44T01T192.168.1.1T", 256);
        strncpy(&res_data[2], "9876543210000T11:22:33:44T01T192.168.1.1T", strnlen("9876543210000T11:22:33:44T01T192.168.1.1T", 256)+1);
        snprintf(&res_data[2+res_data[1]], BUFF_READ_MAX_LEN -res_data[1] - 2,"%ld",data_parse.param.get_data.offset);
        res_data[1]  = strnlen(res_data, 256) - 2;
    }
    response.doResponse(std::string(res_data));

    return;
}

}
