#ifndef __NET_SERVER_RESPONSE_H__
#define __NET_SERVER_RESPONSE_H__

#include <stdint.h>
#include <string>
#include "tc_processor.h"

namespace NetServer {

class Response {

public:

    explicit Response(std::string dest_ip, TcProcessor tc_processor);
    virtual ~Response();

    virtual void doResponse(std::string data);

private:
    std::string dest_ip_;
    TcProcessor tc_processor_;
};

}

#endif

