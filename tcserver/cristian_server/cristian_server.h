#ifndef __CRISTIAN_SERVER_H__
#define __CRISTIAN_SERVER_H__

#include "server.h"

#define CRISTIAN_SERVER_PORT        54320

namespace NetServer {

class CristianServer : Server {

private:

    Processor*  processor_;

protected:

    virtual void Configure(ServerFactory& factory);

public:

    CristianServer();
    virtual ~CristianServer();

    virtual bool Start();
    virtual void Stop();
};

}


#endif

