#ifndef __NET_SERVER_FD_LISTEN_CONNECTION_H__
#define __NET_SERVER_FD_LISTEN_CONNECTION_H__

#include <stdint.h>
#include <sys/socket.h>
#include <sys/select.h>
#include "observer.h"
#include "fdconnection.h"

namespace NetServer {

class FDListenConnection : public FDConnection {

private:

    Observer * observer_;
    void Notify(FDConnection* conn);

public:

    explicit FDListenConnection(int fd, ConnectionType type);
    virtual ~FDListenConnection();

    virtual void OnWantedChanged(ConnectionWanted wantedBit, bool set = true);
    void SetObserver(Observer* observer);

};

}

#endif
