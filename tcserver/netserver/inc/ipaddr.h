#ifndef __NET_SERVER_IP_ADDR_H__
#define __NET_SERVER_IP_ADDR_H__

#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string>

namespace NetServer {

class IPAddr {

private:

    struct sockaddr_in addr_;

public:

    IPAddr();
    virtual ~IPAddr();

    void SetIPAddr(std::string ipAddr);
    void SetPort(uint16_t port);

    struct sockaddr_in GetAddr();

    std::string toString();
    uint16_t toPort();  // host order number

};

}

#endif

