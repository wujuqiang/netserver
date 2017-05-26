#ifndef __NET_SERVER_FD_CONNECTION_H__
#define __NET_SERVER_FD_CONNECTION_H__

#include <stdint.h>
#include <sys/socket.h>
#include <sys/select.h>
#include "ipaddr.h"

namespace NetServer {

class FDConnection {

public:

    typedef enum {

        CONN_STAT_NULL,
        CONN_STAT_LISTEN,       // server listen connection
        CONN_STAT_LINKED,
        CONN_STAT_BREAK,
        CONN_STAT_CLOSE

    } ConnectionState;

    typedef enum {

        CONN_WANT_READ  =     0x01,
        CONN_WANT_WRITE =     0x02

    } ConnectionWanted;

    typedef enum {

        CONN_TYPE_LINK      =     0x01,     // like tcp
        CONN_TYPE_LINKLESS  =     0x02      // like udp

    } ConnectionType;

protected:
    // only for my subclass

    int fd_;

    ConnectionType  type_;
    ConnectionState state_;

    IPAddr peerAddr_;

    uint32_t wanted_;

    void SetWanted(ConnectionWanted wantedBit);
    void ResetWanted(ConnectionWanted wantedBit);

public:

    explicit FDConnection(int fd, ConnectionType type);
    FDConnection(int fd, ConnectionType type, IPAddr peerAddr);
    virtual ~FDConnection();

    virtual void Close();
    virtual int GetFd();
    virtual void ResetFd(int fd);
    virtual IPAddr GetPeerAddr();

    virtual int32_t Read(unsigned char* buf, uint32_t size);
    virtual int32_t Write(unsigned char* buf, uint32_t len);

    virtual void OnWantedChanged(ConnectionWanted wantedBit, bool set = true);
    virtual void OnStateChanged(ConnectionState state);

    virtual ConnectionType  GetType();
    virtual ConnectionState GetState();
    virtual uint32_t GetWanted();

};

}

#endif

