#include "server.h"
#include "utility.h"

using namespace NetServer;

Server::Server()
    : tinaServer_(NULL)
{

}

Server::~Server()
{
    if (tinaServer_) {
        delete tinaServer_;
        tinaServer_ = NULL;
    }
}

void Server::RegProcessor(Processor* processor)
{
    processorList_.push_back(processor);
}

void Server::UnRegProcessor(Processor* processor)
{
    processorList_.remove(processor);
}

bool Server::Start()
{
    ServerFactory factory;

    // call subclass to configure detail.
    Configure(factory);

    tinaServer_ = factory.CreateServer();
    if (NULL == tinaServer_) {
        NS_ERR("Create Tina Server Fail");
        return false;
    }

    for (ProcessorList::iterator it = processorList_.begin(); it != processorList_.end(); it++) {
        tinaServer_->RegProcessor(*it);
    }

    return tinaServer_->Start();
}

void Server::Stop()
{
    if (NULL != tinaServer_) {
        NS_INF("Stop TimeCodeServer");
        tinaServer_->Stop();
    }
}

