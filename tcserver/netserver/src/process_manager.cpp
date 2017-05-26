#include "request.h"
#include "processor_manager.h"
#include "utility.h"

using namespace NetServer;

void ProcessorManager::Notified(FDConnection *conn)
{
    if (NULL != processor_)
    {
        Request req(conn);
        NS_INF("Call Processor to handle Request");
        processor_->doProcess(req);
    }
}

void ProcessorManager::RegProcessor(Processor * processor)
{
    processor_ = processor;
}

void ProcessorManager::UnRegProcessor(Processor * processor)
{
    // FIXME: support multiple processors
    processor_ = NULL;
}
