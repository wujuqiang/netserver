#ifndef __NET_SERVER_PROCESSOR_MANAGER_H__
#define __NET_SERVER_PROCESSOR_MANAGER_H__

#include <stdint.h>
#include "observer.h"
#include "processor.h"

namespace NetServer {

class ProcessorManager : public Observer {

private:
    Processor * processor_;


public:

    void Notified(FDConnection* conn);   // implement Observer

    void RegProcessor(Processor * processor);
    void UnRegProcessor(Processor * processor);

};

}

#endif

