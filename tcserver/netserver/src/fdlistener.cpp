#include "fdlistener.h"

using namespace NetServer;

FDListener::FDListener()
{

}

FDListener::~FDListener()
{

}

void FDListener::SetObserver(Observer *observer)
{
    observer_ = observer;
}
