#ifndef __NET_SERVER_PARSE_H__
#define __NET_SERVER_PARSE_H__

#include <stdint.h>
#include "common_data.h"

namespace NetServer {

class Parse {

public:

    explicit Parse(Data_Parse& data);
    virtual ~Parse();

    virtual Data_Parse getParseData();

private:
    
    Data_Parse& data_parse_;
};

}

#endif

