#include <sys/socket.h>
#include "ipaddr.h"
#include "tcplistener.h"
#include "fdlistenconnection.h"
#include "utility.h"

using namespace NetServer;

TcpListener::TcpListener(IPAddr localAddr)
{
    localAddr_ = localAddr;
}

TcpListener::~TcpListener()
{
    
}

FDConnection* TcpListener::StartListen()
{   
    int err = 0;
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if (-1 == fd) {
        NS_ERR("Create Listen Socket Fail %d", errno);
        NS_ERR("Last Error is %s", strerror(errno));
        return NULL;
    }

    struct sockaddr_in addr_in = localAddr_.GetAddr();

    err = bind(fd, (struct sockaddr*)&addr_in, sizeof(addr_in));

    if (-1 == err) {
        NS_ERR("Bind Socket to %d Fail %d", localAddr_.toPort(), errno);
        NS_ERR("Last Error is %s", strerror(errno));
        return NULL;
    }

    err = listen(fd, 5);

    if (-1 == err) {
        NS_ERR("Listen Socket Fail %d", errno);
        NS_ERR("Last Error is %s", strerror(errno));
        return NULL;
    }

    FDListenConnection* conn = new FDListenConnection(fd, FDConnection::CONN_TYPE_LINK);

    if (NULL != conn) {
        conn->OnStateChanged(FDListenConnection::CONN_STAT_LISTEN);
        conn->SetObserver(observer_);   // notify looper when there is a client connected
        NS_INF("Socket %d Start Listen on %d", fd, localAddr_.toPort());
    } else {
        close(fd);
        NS_ERR("New FDListenConnection Fail! OOM");
    }

    return conn;
}
