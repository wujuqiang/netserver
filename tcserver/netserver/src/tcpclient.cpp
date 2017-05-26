#include "tcpclient.h"
#include "utility.h"

using namespace NetServer;

TCPClient::TCPClient()
{

}

TCPClient::~TCPClient()
{

}

int TCPClient::CreateFD()
{
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (-1 == fd) {
        NS_ERR("Create Client Socket Fail %d", errno);
        NS_ERR("Last Error is %s", strerror(errno));
        return -1;
    }

    struct sockaddr_in addr_in = localAddr_.GetAddr();

    int err = bind(fd, (struct sockaddr*)&addr_in, sizeof(addr_in));

    if (0 != err) NS_ERR("Bind to Local fail!");

    return fd;
}

FDConnection::ConnectionType TCPClient::GetType()
{
    return FDConnection::CONN_TYPE_LINK;
}
