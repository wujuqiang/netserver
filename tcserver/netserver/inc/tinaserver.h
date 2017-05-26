#ifndef __NET_SERVER_TINA_H__
#define __NET_SERVER_TINA_H__

#include "fdlistener.h"
#include "fdlooper.h"
#include "runner.h"
#include "processor_manager.h"

namespace NetServer {

class TinaServer {

private:

    Runner*     runner_;
    FDListener* listener_;
    FDLooper*   looper_;

    ProcessorManager* processorManager_;

public:
    TinaServer();
    virtual ~TinaServer();

    void SetListener(FDListener* listener);
    void SetLooper(FDLooper* looper);

    void RegProcessor(Processor * processor);
    void UnRegProcessor(Processor * processor);

    virtual bool Start();
    virtual void Stop();
};

}

#endif
