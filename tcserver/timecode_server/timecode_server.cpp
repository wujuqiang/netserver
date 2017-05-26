#include "utility.h"
#include "server_factory.h"
#include "timecode_server.h"
//#include "test_timecode_processor.h"
#include "tc_processor.h"

using namespace NetServer;

TimeCodeServer::TimeCodeServer()
    :processor_(NULL)
{

}

TimeCodeServer::~TimeCodeServer()
{
    if (processor_) {
        delete processor_;
        processor_ = NULL;
    }
}

void TimeCodeServer::Configure(ServerFactory& factory)
{
    factory.SetOpt(static_cast<int32_t>(ServerFactory::OPT_TYPE), reinterpret_cast<void*>(ServerFactory::NETSERVER_TCP));
    factory.SetOpt(ServerFactory::OPT_IPADDR, (void*)("0.0.0.0"));
    factory.SetOpt(ServerFactory::OPT_PORT, reinterpret_cast<void*>(TIMECODE_SERVER_PORT));
}

bool TimeCodeServer::Start()
{
    //processor_ = new TestTimeCodeProcessor();
    processor_ = new TcProcessor();
    RegProcessor(processor_);

    NS_INF("Start TimeCodeServer");
    return Server::Start();
}

void TimeCodeServer::Stop()
{
    NS_INF("Stop TimeCodeServer");

    if (processor_) {
        UnRegProcessor(processor_);
        delete processor_;
        processor_ = NULL;
    }

    Server::Stop();
}



