#include <fcntl.h>
#include "fdlistenconnection.h"
#include "utility.h"

using namespace NetServer;

FDListenConnection::FDListenConnection(int fd, ConnectionType type)
    :FDConnection(fd, type)
{
}

FDListenConnection::~FDListenConnection()
{

}

void FDListenConnection::SetObserver(Observer* observer)
{
    observer_ = observer;
}

void FDListenConnection::Notify(FDConnection *conn)
{
    if (NULL != observer_) {
        observer_->Notified(conn);
    }
}

void FDListenConnection::OnWantedChanged(ConnectionWanted wantedBit, bool set)
{
    FDConnection::OnWantedChanged(wantedBit, set);
    if (CONN_STAT_LISTEN == state_ && 0 != (wanted_ & CONN_WANT_READ))
    {
        struct sockaddr_in peerAddr;
        socklen_t peerAddrSize = sizeof(peerAddr);

        int fd = accept(fd_, (struct sockaddr*)&peerAddr, &peerAddrSize);

        if (-1 == fd)
        {
            NS_ERR("accept fail! (%d)", errno);
            NS_ERR("Last Error is %s", strerror(errno));
            return;
        }

#if 0
        // use block socket as requested by processor layer
        int flags = fcntl(fd, F_GETFL, 0);
        int err = fcntl(fd, F_SETFL, flags|O_NONBLOCK);   // set new socket to non-block mode
#endif

        IPAddr peerIPAddr;

        char * szIp = inet_ntoa(peerAddr.sin_addr);
        peerIPAddr.SetIPAddr(std::string(szIp));
        peerIPAddr.SetPort(ntohs(peerAddr.sin_port));

        NS_INF("Accept a new Socket %d from %s", fd, szIp);

        FDConnection* conn = new FDConnection(fd, CONN_TYPE_LINK, peerIPAddr);

        if (NULL != conn) {
            conn->OnStateChanged(CONN_STAT_LINKED);
            Notify(conn);   // notify looper to add a new connection
        } else {
            NS_ERR("New FDConnection Fail OOM!");
        }
    }
}

