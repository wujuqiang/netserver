#include "runner.h"
#include "utility.h"
#include "udplistener.h"
#include "udpclient.h"
#include "pthread_runner.h"

using namespace NetServer;

uint16_t Runner::usedControlPort_ = RUNNER_CONTROL_PORT;

Runner::Runner(FDLooper *looper)
    : looper_(looper)
{
    controlPort_ = GenerateControlPort();
}

Runner::~Runner()
{
    if (0 != loopThread_) {
        NS_WAR("The Runner Thread is still there, forgot stop it?");
    }
}

bool Runner::Run()
{
    bool ok = false;

    if (NULL != looper_) {
        ok = looper_->Loop();
    }

    return ok;
}

bool Runner::RunInThread()
{
    NS_INF("Runner to run in Thread");
    loopThread_ = CreateThread(Runner::RunnerProc, this);

    if (0 == loopThread_) {
        NS_ERR("CreateThread Fail, Can't Run");
        return false;
    }

    return true;
}

void* Runner::RunnerProc(void *runner)
{
    if (NULL == runner) return NULL;

    PThreadRunner* theRunner = static_cast<PThreadRunner*>(runner);
    theRunner->Run();

    return NULL;
}

bool Runner::Start()
{
    if (NULL == looper_) return false;

    // add a control fdconnection into looper.
    // which can break looper once send command to it
    // used to stop looper

    IPAddr addr;
    addr.SetIPAddr("127.0.0.1");
    addr.SetPort(controlPort_);
    UdpListener listener(addr);

    FDConnection* conn = listener.StartListen();

    if (NULL == conn) {
        NS_ERR("Create Server Side of Loop Control Fail!");
        return false;
    }

    looper_->AddConnectionForControl(conn);

    return RunInThread();
}

void Runner::Stop()
{
    if (0 != loopThread_) {

        IPAddr addr;
        UDPClient client;

        addr.SetIPAddr("127.0.0.1");
        addr.SetPort(controlPort_);

        client.SetPeerAddr(addr);
        FDConnection* conn = client.StartConnect();

        Sender sender(conn);
        sender.Write((unsigned char *)LOOP_CTRL_CMD_QUIT, strnlen(LOOP_CTRL_CMD_QUIT, LOOP_CTRL_CMD_MAXLEN));

        WaitThread(loopThread_);
        loopThread_ = 0;
    }
}

uint16_t Runner::GenerateControlPort()
{
    return usedControlPort_++;
}
