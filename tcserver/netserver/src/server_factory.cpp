#include "tcplistener.h"
#include "udplistener.h"
#include "fdlooper.h"
#include "server_factory.h"
#include "utility.h"

using namespace NetServer;


ServerFactory::ServerFactory()
{

}

ServerFactory::~ServerFactory()
{

}

void ServerFactory::SetOpt(int32_t name, void *value)
{
    switch (name) {
    case ServerFactory::OPT_TYPE: {
        type_ = static_cast<NetServerType>(reinterpret_cast<unsigned long>(value));
        break;
    }
    case ServerFactory::OPT_IPADDR: {
        char* szaddr = static_cast<char*>(value);
        std::string ipaddr(szaddr);
        addr_.SetIPAddr(ipaddr);
        break;
    }
    case ServerFactory::OPT_PORT: {
        uint16_t port = static_cast<uint16_t>(reinterpret_cast<unsigned long>(value));
        addr_.SetPort(port);
        break;
    }
    default:
        break;
    }
}

TinaServer* ServerFactory::CreateServer()
{
    TinaServer* server = new TinaServer();

    if (server == NULL) {
        NS_ERR("Create NetServer(%d) Fail!");
        return server;
    }

    switch (type_) {
    case NETSERVER_TCP: {
        if (0== addr_.GetAddr().sin_port) {
            NS_WAR("Bind to a Radom Port? set a IP/Port might be forgotten");
        }
        TcpListener* listener = new TcpListener(addr_);
        FDLooper*    looper = new FDLooper();
        listener->SetObserver(looper);  // let looper know there is a tcp client connected
        server->SetListener(listener);
        server->SetLooper(looper);
        return server;
    }
    case NETSERVER_UDP: {
        if (0== addr_.GetAddr().sin_port) {
            NS_WAR("Bind to a Radom Port? set a IP/Port might be forgotten");
        }
        UdpListener* listener = new UdpListener(addr_);
        FDLooper*    looper = new FDLooper();
        server->SetListener(listener);
        server->SetLooper(looper);
        return server;
        break;
    }
    default:
        break;
    }
    return NULL;
}
