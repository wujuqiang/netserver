#ifndef __NET_SERVER_OBSERVER_H__
#define __NET_SERVER_OBSERVER_H__

#include <stdint.h>
#include "fdconnection.h"

namespace NetServer {

class Observer {

public:

    Observer();
    virtual ~Observer();

    virtual void Notified(FDConnection* conn) = 0;

};

}

#endif
