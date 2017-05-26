#ifndef __TEST_TIMECODE_PROCESSOR_H__
#define __TEST_TIMECODE_PROCESSOR_H__

#include "processor.h"

using namespace NetServer;

class TestTimeCodeProcessor : public Processor
{
public:
    TestTimeCodeProcessor();

    void doProcess(Request& req);
};

#endif
