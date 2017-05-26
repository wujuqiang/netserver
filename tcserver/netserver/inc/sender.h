#ifndef __NET_SERVER_SENDER_H__
#define __NET_SERVER_SENDER_H__

#include <stdint.h>
#include "fdconnection.h"

namespace NetServer {

class Sender {

private:

    FDConnection * conn_;

public:

    explicit Sender(FDConnection* conn);
    virtual ~Sender();

    virtual IPAddr GetPeerAddr();

    virtual int32_t Read(unsigned char* buf, uint32_t size);
    virtual int32_t Write(unsigned char* buf, uint32_t len);
    virtual void Close();

};

}

#endif
