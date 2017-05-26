#ifndef __NET_SERVER_FD_LISTENER_H__
#define __NET_SERVER_FD_LISTENER_H__

#include <stdint.h>
#include "observer.h"
#include "fdconnection.h"

namespace NetServer {

class FDListener {

protected:

    Observer * observer_;

public:

    FDListener();
    virtual ~FDListener();

    void SetObserver(Observer* observer);
    virtual FDConnection* StartListen() = 0;

};

}

#endif
