#include "pthread_runner.h"
#include "tinaserver.h"
#include "utility.h"

using namespace NetServer;

TinaServer::TinaServer()
{
    runner_ = NULL;
    processorManager_ = new ProcessorManager();
}

TinaServer::~TinaServer()
{
    if (NULL != processorManager_) {
        delete processorManager_;
        processorManager_ = NULL;
    }

    if (NULL != runner_) {
        delete runner_;
        runner_ = NULL;
    }

    if (NULL != listener_) {
        delete listener_;
        listener_ = NULL;
    }

    if (NULL != looper_) {
        delete looper_;
        looper_ = NULL;
    }
}

void TinaServer::SetListener(FDListener *listener)
{
    listener_ = listener;
}

void TinaServer::SetLooper(FDLooper *looper)
{
    looper_ = looper;
}

void TinaServer::RegProcessor(Processor * processor)
{
    if (NULL != processorManager_) {
        processorManager_->RegProcessor(processor);
    }
}

void TinaServer::UnRegProcessor(Processor * processor)
{
    if (NULL != processorManager_) {
        processorManager_->UnRegProcessor(processor);
    }
}

bool TinaServer::Start()
{
    if (NULL == looper_ || NULL == listener_) return false;

    FDConnection * conn = listener_->StartListen();

    if (NULL == conn) {
        NS_ERR("Start Listen Fail");
        return false;
    }

    looper_->AddConnection(conn);
    looper_->AddObserver(processorManager_);

    runner_ = new PThreadRunner(looper_);

    if (NULL == runner_) {
        NS_ERR("New Runner Fail OOM!");
        return false;
    }

    bool ok = runner_->Start();

    if (false == ok) {
        NS_ERR("Runner Start Fail!");
        return false;
    }

    return true;
}

void TinaServer::Stop()
{
    if (NULL != runner_) {
        NS_INF("Tina Server Stop Begin");
        runner_->Stop();
        NS_INF("Tina Server Stop End");
    }
}
