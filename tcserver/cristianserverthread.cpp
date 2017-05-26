#include <QDebug>
#include "cristian_server.h"
#include "cristianserverthread.h"

using namespace NetServer;

CristianServerThread::CristianServerThread()
{

}

void CristianServerThread::run()
{
    qDebug() << "CristianServerThread Run ---->";

    CristianServer* server = new CristianServer();
    server->Start();
}


