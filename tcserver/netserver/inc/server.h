#ifndef __NET_SERVER_SERVER_H__
#define __NET_SERVER_SERVER_H__

#include <stdint.h>
#include <list>
#include "processor.h"
#include "tinaserver.h"
#include "server_factory.h"

namespace NetServer {

class Server {

private:

    typedef std::list<Processor*> ProcessorList;

    TinaServer*   tinaServer_;
    ProcessorList processorList_;

protected:

    // subclass must implement this method to configure server.
    virtual void Configure(ServerFactory& factory) = 0;

public:
    Server();
    virtual ~Server();

    virtual void RegProcessor(Processor* processor);
    virtual void UnRegProcessor(Processor* processor);

    virtual bool Start();
    virtual void Stop();

};

}

#endif

