#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/prctl.h>

#include "pthread_runner.h"
#include "utility.h"

using namespace NetServer;

PThreadRunner::PThreadRunner(FDLooper* looper)
    : Runner(looper)
{

}

PThreadRunner::~PThreadRunner()
{

}

uintptr_t PThreadRunner::CreateThread(Runner::RunnerThreadProc proc, Runner* runner)
{
    pthread_t           thd;
    pthread_attr_t      attr;
    struct sched_param  param;
    size_t stack_size = RUNNER_STACKSZ_DEFAULT;

    pthread_attr_init(&attr);
    pthread_attr_getschedparam(&attr, &param);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setstacksize(&attr, stack_size);
    param.sched_priority = sched_get_priority_max(SCHED_OTHER);
    pthread_attr_setschedparam(&attr, &param);

    int ok = pthread_create(&thd, &attr, proc, runner);

    if (ok != 0) {
        NS_ERR("Create pthread Fail %d %s", errno, strerror(errno));
        return 0;
    }

    return static_cast<uintptr_t>(thd);
}

void PThreadRunner::WaitThread(uintptr_t id)
{
    if (0 != id) {
        pthread_join(static_cast<pthread_t>(id), NULL);
    }
}
