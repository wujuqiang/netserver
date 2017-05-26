#include "tc_processor.h"
#include "service_handler_get_tc.h"
#include "service_handler_sync_tc.h"

#include "ipaddr.h"
#include "tcpclient.h"
#include "sender.h"

namespace NetServer{

TcProcessor::TcProcessor()
{

}

TcProcessor::~TcProcessor()
{
    
}

void TcProcessor::doProcess(Request& req)
{
    TC_LOG_DBG("enter!");

    unsigned char buff[BUFF_READ_MAX_LEN] = {'\0'};
    int32_t ret_req = 0;
    ret_req = req.Read(buff, 1);
    if(ret_req <= 0){
        TC_LOG_ERR("read buffer error!");
        return;
    }

    uint8_t type = (uint8_t)buff[0] & 0xff;
    uint8_t len = 0;

    if( (REQ_TYPE_SYNC_TC == type) || (REQ_TYPE_GET_TC == type) ){
        ret_req = req.Read(buff, 1);
        if(ret_req <= 0){
            TC_LOG_ERR("read buffer error!");
            return;
        }
        len = (uint8_t)buff[0] & 0xff;

        //read len data
        ret_req = req.Read(buff, len);
        if(ret_req <= 0){
            TC_LOG_ERR("read buffer error!");
            return;
        }
    }else{
        TC_LOG_ERR("wrong request type(%02x)!", buff[0]);
        return;
    }

    Data_Transfer data_transfer;

    data_transfer.ip = req.GetPeerAddr().toString();
    data_transfer.len = len;
    std::string str((char*)buff);

    ServiceHandler* service = NULL;
    switch(type){
        case REQ_TYPE_SYNC_TC:
            TC_LOG_DBG("type is REQ_TYPE_SYNC_TC.");
            service = new ServiceHandlerSyncTc();
            break;
        case REQ_TYPE_GET_TC:
            TC_LOG_DBG("type is REQ_TYPE_GET_TC.");
            service = new ServiceHandlerGetTc();
            break;
        default:
            TC_LOG_ERR("unknown type=%d.", type);
            break;
    }

    if(NULL != service){
        data_transfer.data = str;
        service->doRequest(data_transfer);
        delete service;
        service = NULL;
    }else{
        TC_LOG_ERR("new ServiceHandler failed.");
    }

    TC_LOG_DBG("exit!");
}

Error_Code TcProcessor::doResponse(Data_Transfer& param)
{
    Error_Code ret = ERROR_CODE_OK;
    //TODO: send responseStr to destIp
    TC_LOG_DBG("doResponse. param is (%s) dest ip is (%s)",param.data.c_str(), param.ip.c_str());

    IPAddr addr;
    addr.SetIPAddr(param.ip.c_str());
    addr.SetPort(12345);

    TCPClient client;
    client.SetPeerAddr(addr);
    FDConnection* conn = client.StartConnect();

    Sender* sender = new Sender(conn);
    if (sender) {
        int32_t len = sender->Write((unsigned char *)param.data.c_str(), param.data.length());
        TC_LOG_DBG("send %d bytes", len);
        sender->Close();
        delete sender;
        sender = NULL;
    }
    return ret;
}

}

