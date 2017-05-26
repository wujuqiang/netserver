#ifndef __TEST_CRISTIAN_PROCESSOR_H__
#define __TEST_CRISTIAN_PROCESSOR_H__

#include "processor.h"

using namespace NetServer;

class TestCristianProcessor : public Processor
{
public:
    TestCristianProcessor();

    void doProcess(Request& req);
};

#endif

