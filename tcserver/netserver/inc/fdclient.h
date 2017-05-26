#ifndef __NET_SERVER_FD_CLIENT_H__
#define __NET_SERVER_FD_CLIENT_H__

#include "fdconnection.h"

namespace NetServer {

class FDClient {

protected:

    IPAddr localAddr_;
    IPAddr peerAddr_;

    virtual int CreateFD() = 0;
    virtual FDConnection::ConnectionType GetType() = 0;

public:

    FDClient();
    FDClient(FDConnection* conn);

    virtual ~FDClient();

    void SetLocalAddr(IPAddr addr);
    void SetPeerAddr(IPAddr addr);

    virtual FDConnection* StartConnect();
};

}

#endif

