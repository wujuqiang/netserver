#include "observable.h"

using namespace NetServer;

Observable::Observable()
{
    observerList_.empty();
}

Observable::~Observable()
{

}

void Observable::AddObserver(Observer* observer)
{
    observerList_.push_back(observer);
}

void Observable::RemoveObserver(Observer* observer)
{
    observerList_.remove(observer);
}

void Observable::Notify(FDConnection* conn)
{
    for (ObserverList::iterator it = observerList_.begin(); it != observerList_.end(); it++) {
        Observer* observer = *it;
        if (NULL != observer) {
            observer->Notified(conn);
        }
    }
}
