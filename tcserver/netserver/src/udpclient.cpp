#include "udpclient.h"
#include "utility.h"

using namespace NetServer;

UDPClient::UDPClient()
{

}

UDPClient::~UDPClient()
{

}

int UDPClient::CreateFD()
{
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

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

FDConnection::ConnectionType UDPClient::GetType()
{
    return FDConnection::CONN_TYPE_LINKLESS;
}
