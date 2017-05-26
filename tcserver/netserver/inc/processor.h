#ifndef __NET_SERVER_PROCESSOR_H__
#define __NET_SERVER_PROCESSOR_H__

#include <stdint.h>
#include "request.h"

namespace NetServer {

class Processor {

private:

public:

    Processor() {}
    virtual ~Processor() {}

    virtual void doProcess(Request& req) = 0;

};

}

#endif
