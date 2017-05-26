#ifndef __NET_SERVER_REQUEST_H__
#define __NET_SERVER_REQUEST_H__

#include <stdint.h>
#include "fdconnection.h"

namespace NetServer {

class Request {

private:

    FDConnection * conn_;

public:

    explicit Request(FDConnection* conn);
    virtual ~Request();

    virtual IPAddr GetPeerAddr();

    virtual int32_t Read(unsigned char* buf, uint32_t size);
    virtual int32_t Write(unsigned char* buf, uint32_t len);

};

}

#endif
