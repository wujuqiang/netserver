#include <sys/socket.h>
#include "ipaddr.h"
#include "udplistener.h"
#include "utility.h"

using namespace NetServer;

UdpListener::UdpListener(IPAddr localAddr)
{
    localAddr_ = localAddr;
}

UdpListener::~UdpListener()
{

}

FDConnection* UdpListener::StartListen()
{
    int err = 0;
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

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

    FDConnection* conn = new FDConnection(fd, FDConnection::CONN_TYPE_LINKLESS);

    if (NULL != conn) {
        NS_INF("Socket %d Start Listen on %d", fd, localAddr_.toPort());
    } else {
        close(fd);
        NS_ERR("New FDListenConnection Fail! OOM");
    }

    return conn;
}

