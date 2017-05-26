#ifndef __NET_SERVER_FACTORY_H__
#define __NET_SERVER_FACTORY_H__

#include <stdint.h>
#include "ipaddr.h"
#include "tinaserver.h"

namespace NetServer {

class ServerFactory {

public:

    typedef enum {

        NETSERVER_TCP = 0,
        NETSERVER_UDP

    } NetServerType;

private:

    NetServerType type_;
    IPAddr addr_;

public:

    ServerFactory();
    ~ServerFactory();

    static const int32_t OPT_TYPE       = 0x01;
    static const int32_t OPT_IPADDR     = 0x02;
    static const int32_t OPT_PORT       = 0x03;

    void SetOpt(int32_t name, void* value);
    TinaServer* CreateServer();

};

}

#endif
