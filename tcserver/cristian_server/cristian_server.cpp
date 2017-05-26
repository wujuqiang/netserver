#include "utility.h"
#include "server_factory.h"
#include "cristian_server.h"
//#include "test_cristian_processor.h"
#include "cristian_processor.h"

using namespace NetServer;

CristianServer::CristianServer()
    :processor_(NULL)
{

}

CristianServer::~CristianServer()
{
    if (processor_) {
        delete processor_;
        processor_ = NULL;
    }
}

void CristianServer::Configure(ServerFactory& factory)
{
    factory.SetOpt(static_cast<int32_t>(ServerFactory::OPT_TYPE), reinterpret_cast<void*>(ServerFactory::NETSERVER_UDP));
    factory.SetOpt(ServerFactory::OPT_IPADDR, (void*)("0.0.0.0"));
    factory.SetOpt(ServerFactory::OPT_PORT, reinterpret_cast<void*>(CRISTIAN_SERVER_PORT));
}

bool CristianServer::Start()
{
    //processor_ = new TestCristianProcessor();
    processor_ = new CristianProcessor();
    RegProcessor(processor_);

    NS_INF("Start CristianServer");
    return Server::Start();
}

void CristianServer::Stop()
{
    NS_INF("Stop CristianServer");

    if (processor_) {
        UnRegProcessor(processor_);
        delete processor_;
        processor_ = NULL;
    }

    Server::Stop();
}


