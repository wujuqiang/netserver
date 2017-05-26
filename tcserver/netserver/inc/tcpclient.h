#ifndef __NET_SERVER_TCP_CLIENT_H__
#define __NET_SERVER_TCP_CLIENT_H__

#include "fdclient.h"

namespace NetServer {

class TCPClient : public FDClient {

private:

public:

    TCPClient();
    virtual ~TCPClient();

    virtual int CreateFD();
    virtual FDConnection::ConnectionType GetType();
};

}

#endif

