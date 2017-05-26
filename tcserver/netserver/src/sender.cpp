#include "sender.h"

using namespace NetServer;

Sender::Sender(FDConnection *conn)
{
    conn_ = conn;
}

Sender::~Sender()
{
    if (conn_) {
        conn_->Close();
        delete conn_;
        conn_ = NULL;
    }
}

IPAddr Sender::GetPeerAddr()
{
    IPAddr addr;
    if (NULL != conn_) {
        return conn_->GetPeerAddr();
    }
    return addr;
}

int32_t Sender::Read(unsigned char* buf, uint32_t size)
{
    if (NULL != conn_)
    {
        return conn_->Read(buf, size);
    }

    return -1;
}

int32_t Sender::Write(unsigned char* buf, uint32_t len)
{
    if (NULL != conn_)
    {
        return conn_->Write(buf, len);
    }

    return -1;
}

void Sender::Close()
{
    if (NULL != conn_)
    {
        return conn_->Close();
    }
}

