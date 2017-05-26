#ifndef __NET_SERVER_DUMMY_SERVICE_H__
#define __NET_SERVER_DUMMY_SERVICE_H__

#include "service.h"

namespace NetServer {

class DummyService:public Service {

public:

    DummyService();
    virtual ~DummyService();

    virtual void handler(Parse data, Response response);

};

}

#endif

