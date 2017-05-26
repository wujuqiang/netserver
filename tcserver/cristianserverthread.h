#ifndef CRISTIANSERVERTHREAD_H
#define CRISTIANSERVERTHREAD_H

#include <QThread>

class CristianServerThread : public QThread
{
public:
    CristianServerThread();

protected:
    void run();
};

#endif // CRISTIANSERVERTHREAD_H
