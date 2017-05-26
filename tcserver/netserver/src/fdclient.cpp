#include "fdclient.h"
#include "utility.h"

using namespace NetServer;

FDClient::FDClient()
{
    memset(&localAddr_, 0x00, sizeof(localAddr_));
    memset(&peerAddr_, 0x00, sizeof(peerAddr_));
}

FDClient::~FDClient()
{

}

void FDClient::SetLocalAddr(IPAddr addr)
{
    localAddr_ = addr;
}

void FDClient::SetPeerAddr(IPAddr addr)
{
    peerAddr_ = addr;
}

FDConnection* FDClient::StartConnect()
{
    if (0 == peerAddr_.toPort() || 0 == peerAddr_.GetAddr().sin_addr.s_addr) {
        NS_ERR("Invalid Peer Addr");
        return false;
    }

    int fd = CreateFD();
    FDConnection::ConnectionType type = GetType();

    if (-1 == fd) return NULL;

    struct sockaddr_in peerAddrIn = peerAddr_.GetAddr();

    int err = connect(fd, (sockaddr*)&peerAddrIn, sizeof(peerAddrIn));

    if (0 != err) {
        NS_ERR("connect to %s:%d fail!", peerAddr_.toString().c_str(), peerAddr_.toPort());
        NS_ERR("Error is %d, %s", errno, strerror(errno));
        close(fd);
        return NULL;
    }

    FDConnection* conn = new FDConnection(fd, type);

    if (NULL == conn) {
        NS_ERR("New FDConnection Fail! OOM");
        close(fd);
        return NULL;
    }

    conn->OnStateChanged(FDConnection::CONN_STAT_LINKED);
    conn->OnWantedChanged(FDConnection::CONN_WANT_WRITE);

    return conn;
}
