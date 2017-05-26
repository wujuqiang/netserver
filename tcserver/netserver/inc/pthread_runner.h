#ifndef __PTHEAD_RUNNER_H__
#define __PTHEAD_RUNNER_H__

#include "runner.h"

namespace NetServer {

class PThreadRunner : public Runner {

private:

    virtual uintptr_t CreateThread(Runner::RunnerThreadProc proc, Runner* runner);
    virtual void      WaitThread(uintptr_t id);

    static void* DefThreadProc(void* arg);

public:

    explicit PThreadRunner(FDLooper* looper);
    virtual ~PThreadRunner();
};

}

#endif

