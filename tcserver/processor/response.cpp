#include "response.h"

namespace NetServer {

Response::Response(std::string dest_ip, TcProcessor tc_processor)
: tc_processor_(tc_processor)
, dest_ip_(dest_ip)
{

}

Response::~Response()
{
    
}

void Response::doResponse(char* data, unsigned int len)
{
    Data_Transfer param;
    memset(&param,0,sizeof(param));
    param.len = len;
    memcpy(param.data,data,len+1);
    strncpy(param.ip,dest_ip_.c_str(),BUFF_IP_MAX_LEN);
    tc_processor_.doResponse(param);
    return;
}

}

