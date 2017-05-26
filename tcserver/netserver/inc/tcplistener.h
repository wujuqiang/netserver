#ifndef __NET_SERVER_TCP_LISTENER_H__
#define __NET_SERVER_TCP_LISTENER_H__

#include <stdint.h>
#include "ipaddr.h"
#include "fdlistener.h"

namespace NetServer {

class TcpListener : public FDListener {

private:

    IPAddr localAddr_;

public:

    explicit TcpListener(IPAddr localAddr);
    virtual ~TcpListener();

    virtual FDConnection* StartListen();

};

}

#endif

