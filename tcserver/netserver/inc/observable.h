#ifndef __NET_SERVER_OBSERVABLE_H__
#define __NET_SERVER_OBSERVABLE_H__

#include <stdint.h>
#include <list>
#include "observer.h"

namespace NetServer {

typedef std::list<Observer *> ObserverList;

class Observable {

private:

    ObserverList observerList_;

public:

    Observable();
    virtual ~Observable();

    virtual void AddObserver(Observer* observer);
    virtual void RemoveObserver(Observer* observer);

    virtual void Notify(FDConnection* conn);

};

}

#endif

