#include "cristian_processor.h"

#include <sys/time.h>

namespace NetServer{

CristianProcessor::CristianProcessor()
{

}

CristianProcessor::~CristianProcessor()
{
    
}

void CristianProcessor::doProcess(Request& req)
{
    //check req null???
    TC_LOG_DBG("enter!");

    unsigned char buff[MILLISCONDS_MAX_LEN+1] = {'\0'};
    int32_t ret_req = 0;
    ret_req = req.Read(buff, MILLISCONDS_MAX_LEN);
    buff[MILLISCONDS_MAX_LEN] = '\0';

    if(ret_req > 0){
        std::string str = getResponseData(buff);
        //TC_LOG_DBG("response is (%s)", str.c_str());

        req.Write((unsigned char*)str.c_str(), str.length());
    }else{
        TC_LOG_ERR("request data error is (%s)", buff);
    }

    TC_LOG_DBG("exit!");
}

uint64_t CristianProcessor::getSystemCounts()
{
    uint64_t ret = 1234567890000000;
    /*OSAL_ERR err = osal_get_syscnt(&ret);	
    if (OSAL_ERR_OK != err) {		
        TC_LOG_ERR("[CristianProcessorImpl] osal_get_syscnt error.");		
        return 0;	
    }*/

    struct timeval tv;
    gettimeofday(&tv,NULL);

    return (tv.tv_sec*1000 + tv.tv_usec/1000);

    //return (ret /1000);
}

std::string CristianProcessor::getResponseData(unsigned char* request_data)
{
    std::string str_t1;
    std::string str_t2;
    std::string str_t3;

    str_t1 = std::string((char*)request_data);

    char char_t2[MILLISCONDS_MAX_LEN+1] = {'\0'};
    snprintf(char_t2, sizeof(char_t2), "%lu", getSystemCounts());

    str_t2 = std::string(char_t2);

    char char_t3[MILLISCONDS_MAX_LEN+1] = {'\0'};
    snprintf(char_t3, sizeof(char_t3), "%lu", getSystemCounts());

    str_t3 = std::string(char_t3);

    return (str_t1 + "T" + str_t2 + "T" + str_t3);
}

}
