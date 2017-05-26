#ifndef __NET_SERVER_RUNNER_H__
#define __NET_SERVER_RUNNER_H__

#include <stdint.h>
#include "fdlooper.h"
#include "sender.h"

#define RUNNER_CONTROL_PORT     17595
#define RUNNER_STACKSZ_DEFAULT  (64*1024)

namespace NetServer {

class Runner {

protected:

    typedef void* (*RunnerThreadProc)(void* runner);
    static void *RunnerProc(void* runner);

private:

    FDLooper*   looper_;
    uintptr_t   loopThread_;

    static uint16_t usedControlPort_;
    int16_t controlPort_;

    virtual bool Run();
    virtual bool RunInThread();
    virtual uint16_t GenerateControlPort();

    virtual uintptr_t CreateThread(RunnerThreadProc proc, Runner* runner) = 0;
    virtual void      WaitThread(uintptr_t id) = 0;

public:

    explicit Runner(FDLooper* looper);
    virtual ~Runner();

    virtual bool Start();
    virtual void Stop();
};

}

#endif
