#ifndef __NET_SERVER_UDP_CLIENT_H__
#define __NET_SERVER_UDP_CLIENT_H__

#include "fdclient.h"

namespace NetServer {

class UDPClient : public FDClient {

private:

public:

    UDPClient();
    virtual ~UDPClient();

    virtual int CreateFD();
    virtual FDConnection::ConnectionType GetType();
};

}

#endif

