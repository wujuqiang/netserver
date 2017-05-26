#ifndef TCSYNCSERVERTHREAD_H
#define TCSYNCSERVERTHREAD_H

#include <QThread>

class TCSyncServerThread : public QThread
{
public:
    TCSyncServerThread();
    virtual ~TCSyncServerThread();

protected:
    void run();
};

#endif // TCSYNCSERVERTHREAD_H
