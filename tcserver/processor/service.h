#ifndef __NET_SERVER_SERVICE_H__
#define __NET_SERVER_SERVICE_H__

#include <stdint.h>
#include "parse.h"
#include "response.h"

namespace NetServer {

class Service {

public:

    Service() {}
    virtual ~Service() {}

    virtual void handler(Parse data, Response response) = 0;

};

}

#endif
