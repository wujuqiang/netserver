#ifndef __UDP_LISTENER_H__
#define __UDP_LISTENER_H__

#include <stdint.h>
#include "ipaddr.h"
#include "fdlistener.h"

namespace NetServer {

class UdpListener : public FDListener {

private:

    IPAddr localAddr_;

public:

    explicit UdpListener(IPAddr localAddr);
    virtual ~UdpListener();

    virtual FDConnection* StartListen();

};

}

#endif

