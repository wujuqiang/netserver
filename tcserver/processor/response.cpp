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

void Response::doResponse(std::string data)
{
    Data_Transfer param;
    param.data = data;
    param.ip = dest_ip_;
    tc_processor_.doResponse(param);
    return;
}

}

