#include "fdlooper.h"
#include "utility.h"

using namespace NetServer;

FDLooper::FDLooper()
    : break_(false),
      fd_control_(-1)
{

}

FDLooper::~FDLooper()
{
    for (FdMap::iterator it = watchFds_.begin(); it != watchFds_.end(); it++)
    {
        FDConnection * conn = it->second;
        if (NULL != conn) {
            conn->Close();
            delete conn;
        }
    }
}

// add connection for accept from listener or
// add connection from return of accept
void FDLooper::AddConnection(FDConnection *conn)
{
    int fd = conn->GetFd();
    watchFds_.insert(FdPair(fd, conn));
    NS_INF("Add a new Socket %d into looper", fd);
}

void FDLooper::AddConnectionForControl(FDConnection* conn)
{
    if (NULL != conn) {
        fd_control_ = conn->GetFd();
        AddConnection(conn);
    }
}

void FDLooper::DeleteConnection(FDConnection *conn)
{
    int fd = conn->GetFd();
    NS_INF("Close Socket %d and Delete FDConnection", fd);

    close(fd);
    watchFds_.erase(fd);
    delete conn;
}

FDLooper::LoopCtrlCmd FDLooper::ReadControlCmd(FDConnection *conn)
{
    if (NULL != conn) {

        unsigned char szCmd[LOOP_CTRL_CMD_MAXLEN+1] = {0};

        int len = conn->Read(szCmd, LOOP_CTRL_CMD_MAXLEN);
        szCmd[len] = 0x00;

        if (0 == strncmp(reinterpret_cast<const char*>(szCmd), LOOP_CTRL_CMD_QUIT, len)) {
            return LOOP_CTRL_QUIT;
        }
    }

    return LOOP_CTRL_UNKWN;
}

int FDLooper::ResetRfds()
{
    int MaxFd = 0;

    FD_ZERO(&FdsRead_);
    FD_ZERO(&FdsWrite_);
    FD_ZERO(&FdsExcept_);

    for (FdMap::iterator it = watchFds_.begin(); it != watchFds_.end(); it++)
    {
        int fd = it->first;

        FD_SET(fd, &FdsRead_);
        //FD_SET(fd, &FdsWrite_);   // after accept a socket, its FD_WRITE cause select always return.
        FD_SET(fd, &FdsExcept_);

        if (fd > MaxFd) MaxFd = fd;
    }

    return MaxFd;
}

void FDLooper::OnFdChange()
{
    for (FdMap::iterator it = watchFds_.begin(); it != watchFds_.end(); it++)
    {
        int fd = it->first;
        FDConnection * conn = it->second;

        if (NULL == conn) continue;

        if (FD_ISSET(fd, &FdsRead_)) {
            // socket can recv
            NS_INF("Detach READ event on Socket %d", fd);
            conn->OnWantedChanged(FDConnection::CONN_WANT_READ);

            if (fd == fd_control_) {
                FDLooper::LoopCtrlCmd cmd = ReadControlCmd(conn);
                if (LOOP_CTRL_QUIT == cmd) {
                    NS_WAR("Recv Quit Cmd from Loop Control!");
                    Break();
                    break;
                }
            } else if (conn->GetState() != FDConnection::CONN_STAT_LISTEN) {

                if (conn->GetType() == FDConnection::CONN_TYPE_LINKLESS) {
                    FDConnection* cloneConn = new FDConnection(conn->GetFd(), conn->GetType());
                    cloneConn->OnWantedChanged(FDConnection::CONN_WANT_READ);
                    Notify(cloneConn);

                } else {

                    Notify(conn);   // notify processor manager
                }
            }
        }

        if (FD_ISSET(fd, &FdsWrite_)) {
            // socket can send
            conn->OnWantedChanged(FDConnection::CONN_WANT_WRITE);
        }

        if (FD_ISSET(fd, &FdsExcept_)) {
            // socket error
        }

        if (FDConnection::CONN_STAT_CLOSE == conn->GetState() || FDConnection::CONN_STAT_BREAK == conn->GetState()) {
            DeleteConnection(conn);
        }
    }
}

// this function will not return if success
bool FDLooper::Loop()
{
    NS_INF("Fall into dead loop to detach socket event...");

    while (1) {

        if (true == break_) break;

        int maxFd = ResetRfds();
        maxFd++;

        struct timeval tv;
        tv.tv_sec = 5;
        tv.tv_usec = 0;

       int retval = select(maxFd, &FdsRead_, &FdsWrite_, &FdsExcept_, &tv);

       if (retval == -1) {

           NS_ERR("select Failed in FDLooper!");
           return false;

       } else if (retval) {

            OnFdChange(); 
            if (true == break_) break;

       } else {
           // no data within 5s
           ;
       }
    }

    NS_INF("Jump out from dead loop of detaching socket event");

    return true;
}

// break loop
void FDLooper::Break()
{
    break_ = true;
}

void FDLooper::Notified(FDConnection *conn)
{
    AddConnection(conn);
}
