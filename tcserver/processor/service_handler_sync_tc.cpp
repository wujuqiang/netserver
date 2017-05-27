#include "service_handler_sync_tc.h"
#include "string.h"
#include "parse.h"
#include "response.h"
#include "dummy_service.h"
#include "tc_processor.h"

namespace NetServer{

ServiceHandlerSyncTc::ServiceHandlerSyncTc()
{

}

ServiceHandlerSyncTc::~ServiceHandlerSyncTc()
{

}

void ServiceHandlerSyncTc::doRequest(Data_Transfer& param)
{
    TC_LOG_DBG("enter!");
    if(0 == checkDataValid(std::string(param.data))){
        //receive data format is NG.
        TC_LOG_ERR("not valid data. data is (%s)", param.data);
        return;
    }
    Data_Parse data_parse;
    memset(&data_parse,0,sizeof(data_parse));
    parseData(data_parse, std::string(param.data));

    TC_LOG_DBG("mi:%lu, p:%02X, s:%02X, m:%02X, h:%02X, auto:%d", 
		data_parse.param.sync_data.milli_seconds, data_parse.param.sync_data.tc_p, data_parse.param.sync_data.tc_s, 
		data_parse.param.sync_data.tc_m, data_parse.param.sync_data.tc_h, data_parse.param.sync_data.auto_flag);
    //TODO

    Parse parse(data_parse);
    TcProcessor tc_processor;
    Response response(std::string(param.ip), tc_processor);

    DummyService dummy_service;
    dummy_service.handler(parse, response);

}

uint8_t ServiceHandlerSyncTc::checkDataValid(std::string src)
{
    uint8_t ret = 0;
    static const uint8_t COLON_NUM = 3;
    static const uint8_t CHAR_T_NUM = 2;
    static const char CHAR_T = 'T';
    static const char CHAR_COLON = ':';

    uint8_t colun_cnt = 0;
    uint8_t char_t_cnt = 0;

    char tmp_src[BUFF_READ_MAX_LEN] = {'\0'};
    if(src.length() >= BUFF_READ_MAX_LEN - 1){
        return 0;
    }

    strncpy(tmp_src, src.c_str(), src.length()+1);
    tmp_src[src.length()] = '\0';
    for(int i=0;i<src.length();i++){
        if(CHAR_COLON == tmp_src[i]){
            colun_cnt++;
        }else if(CHAR_T == tmp_src[i]){
            char_t_cnt++;
        }
    }

    if( (COLON_NUM == colun_cnt) && (CHAR_T_NUM == char_t_cnt)){
        ret = 1;
    }
    
    return ret;
}

void ServiceHandlerSyncTc::parseData(Data_Parse& out, std::string src)
{
    TC_LOG_DBG("ParseData.data is (%s)", src.c_str());

    char tmp_src[BUFF_READ_MAX_LEN] = {'\0'};

    strncpy(tmp_src, src.c_str(), src.length()+1);
    tmp_src[src.length()] = '\0';

    std::string str_array[SYNC_DATA_PARSE_MAX];

    const char* split = "T:";
    char *context = NULL;

    char* split_result = strtok_r(tmp_src, split, &context);

    int index = 0;
    while(split_result){
        str_array[index] = split_result;
        TC_LOG_DBG("index=%d, data=%s", index, str_array[index].c_str());
        index++;
        if(index >= SYNC_DATA_PARSE_MAX){
            break;
        }
        split_result = strtok_r(NULL, split, &context);
    }

    out.type = REQ_TYPE_SYNC_TC;
    out.param.sync_data.milli_seconds = (uint64_t)strtoull(str_array[SYNC_DATA_PARSE_MILLSECONDS].c_str(), NULL, TRANSFER_DATA_DECIMAL);

    out.param.sync_data.tc_p = (uint8_t)strtol(str_array[SYNC_DATA_PARSE_TC_P].c_str(), NULL, TRANSFER_DATA_HEXADECIMAL);
    out.param.sync_data.tc_s = (uint8_t)strtol(str_array[SYNC_DATA_PARSE_TC_S].c_str(), NULL, TRANSFER_DATA_HEXADECIMAL);
    out.param.sync_data.tc_m = (uint8_t)strtol(str_array[SYNC_DATA_PARSE_TC_M].c_str(), NULL, TRANSFER_DATA_HEXADECIMAL);
    out.param.sync_data.tc_h = (uint8_t)strtol(str_array[SYNC_DATA_PARSE_TC_H].c_str(), NULL, TRANSFER_DATA_HEXADECIMAL);
    out.param.sync_data.auto_flag = (uint8_t)strtol(str_array[SYNC_DATA_PARSE_AUTO_FLAG].c_str(), NULL, TRANSFER_DATA_DECIMAL);

}

}

