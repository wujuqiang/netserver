#include <QDebug>
#include "timecode_server.h"
#include "tcsyncserverthread.h"

using namespace NetServer;

TCSyncServerThread::TCSyncServerThread()
{

}

TCSyncServerThread::~TCSyncServerThread()
{

}

void TCSyncServerThread::run()
{
    qDebug() << "TCSyncServerThread Run ---->";

    TimeCodeServer* server = new TimeCodeServer();
    server->Start();
}

