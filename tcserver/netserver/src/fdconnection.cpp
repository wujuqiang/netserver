#include "fdconnection.h"
#include "utility.h"

using namespace NetServer;

FDConnection::FDConnection(int fd, ConnectionType type)
    : fd_(fd),
      type_(type)
{

}

FDConnection::FDConnection(int fd, ConnectionType type, IPAddr peerAddr)
    :fd_(fd),
     type_(type),
     peerAddr_(peerAddr)
{

}

FDConnection::~FDConnection()
{
    if (-1 != fd_) {
        close(fd_);
        fd_ = -1;
    }
}

void FDConnection::Close()
{
    if (-1 != fd_) {
        close(fd_);
        fd_ = -1;
    }
}

int FDConnection::GetFd()
{
    return fd_;
}

void FDConnection::ResetFd(int fd)
{
    fd_ = fd;
}

IPAddr FDConnection::GetPeerAddr()
{
    return peerAddr_;
}

FDConnection::ConnectionState FDConnection::GetState()
{
    return state_;
}

FDConnection::ConnectionType  FDConnection::GetType()
{
    return type_;
}

uint32_t FDConnection::GetWanted()
{
    return wanted_;
}

int32_t FDConnection::Read(unsigned char* buf, uint32_t size)
{
    if ( CONN_TYPE_LINKLESS == type_ ||
         (CONN_TYPE_LINK == type_ || CONN_STAT_LINKED == state_) ) {

        ssize_t t = 0;

        if (CONN_TYPE_LINKLESS == type_ && CONN_STAT_LINKED != state_) {
            // it's an linkless Connection like UDP and not call connect, maybe a virtual connection
            struct sockaddr_in Addr;
            socklen_t AddrSize = sizeof(Addr);

            t = recvfrom(fd_, buf, size, 0, (struct sockaddr*)&Addr, &AddrSize);

            if (t > 0) {

                char * szIp = inet_ntoa(Addr.sin_addr);
                peerAddr_.SetIPAddr(std::string(szIp));
                peerAddr_.SetPort(ntohs(Addr.sin_port));

                NS_INF("Linkless Socket %d receive from %s:%d", fd_, szIp, peerAddr_.toPort());
            }
        } else {

            t = recv(fd_, buf, size, 0);
        }

        if (0 == t) {

            NS_INF("Remote Socket %d closed in order", fd_);
            OnStateChanged(CONN_STAT_CLOSE);
            return -1; // close means fail here

        } else if (-1 == t) {

            NS_INF("Read Socket %d Failed with %d", fd_, errno);

            if (EAGAIN == t || EWOULDBLOCK == t) {

                // only for none block socket
                NS_WAR("No More Data for Now to Read");
                OnWantedChanged(CONN_WANT_READ, false);
                return 0;

            } else {
                OnStateChanged(CONN_STAT_BREAK);
                return -1;
            }
        } else {
            // TODO: will FD_READ come when read part of data?
            OnWantedChanged(CONN_WANT_READ, false);
            return t;
        }
    }

    return -1;
}

int32_t FDConnection::Write(unsigned char* buf, uint32_t len)
{   
    if ( CONN_TYPE_LINKLESS == type_ ||
         (CONN_TYPE_LINK == type_ || CONN_STAT_LINKED == state_) ) {

        ssize_t t = 0;

        if (CONN_TYPE_LINKLESS == type_ && CONN_STAT_LINKED != state_) {
            // it's an linkless Connection like UDP and not call connect, maybe a virtual connection

            struct sockaddr_in Addr = peerAddr_.GetAddr();
            socklen_t AddrSize = sizeof(Addr);

            if (peerAddr_.toPort() == 0) {
                NS_ERR("Write to a Connection not linked and invalid Peer Addr, Fail");
                return -1;
            }

            t = sendto(fd_, buf, len, 0, (struct sockaddr*)&Addr, AddrSize);

        } else {

            t = send(fd_, buf, len, 0);
        }

        if (-1 == t) {
            NS_ERR("Send Fail %d %s", errno, strerror(errno));
            OnStateChanged(CONN_STAT_BREAK);
        }

        return t;
    }

    return -1;
}

void FDConnection::OnStateChanged(ConnectionState state)
{
    state_ = state;
}

void FDConnection::OnWantedChanged(ConnectionWanted wantedBit, bool set)
{
    if (set)
        wanted_ |= wantedBit;
    else
        wanted_ &= ~wantedBit;
}
