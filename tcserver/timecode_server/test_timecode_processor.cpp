#include "utility.h"
#include "test_timecode_processor.h"

TestTimeCodeProcessor::TestTimeCodeProcessor()
{

}

void TestTimeCodeProcessor::doProcess(Request &req)
{
    unsigned char szOut[100+1] = {};
    int32_t len = req.Read(szOut, 100);
    szOut[len] = 0;

    NS_INF("Process [%s] req from %s", szOut, req.GetPeerAddr().toString().c_str());
}

