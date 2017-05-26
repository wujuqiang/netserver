#ifndef __TIME_CODE_SERVER_H__
#define __TIME_CODE_SERVER_H__

#include "server.h"

#define TIMECODE_SERVER_PORT        54321

namespace NetServer {

class TimeCodeServer : public Server {

private:

    Processor*  processor_;

protected:

    virtual void Configure(ServerFactory& factory);

public:

    TimeCodeServer();
    virtual ~TimeCodeServer();

    virtual bool Start();
    virtual void Stop();

};

}


#endif

