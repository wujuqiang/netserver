#include "request.h"

using namespace NetServer;

Request::Request(FDConnection *conn)
{
    conn_ = conn;
}

Request::~Request()
{
    if (conn_->GetType() == FDConnection::CONN_TYPE_LINKLESS) {
        // this connection should be a clone connection from looper
        conn_->ResetFd(-1);
        delete conn_;
        conn_ = NULL;
    }
}

IPAddr Request::GetPeerAddr()
{
    IPAddr addr;
    if (NULL != conn_) {
        return conn_->GetPeerAddr();
    }
    return addr;
}

int32_t Request::Read(unsigned char* buf, uint32_t size)
{
    if (NULL != conn_)
    {
        return conn_->Read(buf, size);
    }

    return -1;
}

int32_t Request::Write(unsigned char* buf, uint32_t len)
{
    if (NULL != conn_)
    {
        return conn_->Write(buf, len);
    }

    return -1;
}


