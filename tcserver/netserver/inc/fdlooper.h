#ifndef __NET_SERVER_FD_LOOPER_H__
#define __NET_SERVER_FD_LOOPER_H__

#include <stdint.h>
#include <sys/select.h>
#include <map>
#include "observer.h"
#include "observable.h"
#include "fdconnection.h"

#define LOOP_CTRL_CMD_MAXLEN    32
#define LOOP_CTRL_CMD_QUIT      "quit"

namespace NetServer {

class FDLooper : public Observer, public Observable {

private:

    typedef std::map<int, FDConnection*> FdMap;
    typedef std::pair<int, FDConnection*> FdPair;

    typedef enum {

        LOOP_CTRL_UNKWN = 0,
        LOOP_CTRL_QUIT = 1

    } LoopCtrlCmd;

    bool break_;

    fd_set FdsRead_;
    fd_set FdsWrite_;
    fd_set FdsExcept_;

    int   fd_control_;
    FdMap watchFds_;

    int ResetRfds();
    void OnFdChange();

    void DeleteConnection(FDConnection* conn);
    LoopCtrlCmd ReadControlCmd(FDConnection* conn);

    void Break();

public:

    FDLooper();
    virtual ~FDLooper();

    // add connection for accept from listener or
    // add connection from return of accept
    virtual void AddConnection(FDConnection* conn);

    virtual void AddConnectionForControl(FDConnection* conn);

    // this function will not return if success
    virtual bool Loop();

    virtual void Notified(FDConnection *conn);
};

}

#endif

