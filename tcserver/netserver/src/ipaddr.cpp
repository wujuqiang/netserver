#include <string.h>
#include "ipaddr.h"

using namespace NetServer;

IPAddr::IPAddr()
{
    memset(&addr_, 0x00, sizeof(addr_));
    addr_.sin_family = AF_INET;
}

IPAddr::~IPAddr()
{

}

void IPAddr::SetIPAddr(std::string ipAddr)
{
    inet_aton(ipAddr.c_str(), &(addr_.sin_addr));
}

void IPAddr::SetPort(uint16_t port)
{
    addr_.sin_port = htons(port);
}

struct sockaddr_in IPAddr::GetAddr()
{
    return addr_;
}

std::string IPAddr::toString()
{
    std::string str(inet_ntoa(addr_.sin_addr));
    return str;
}

uint16_t IPAddr::toPort()
{
    return ntohs(addr_.sin_port);
}
