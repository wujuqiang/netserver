#include "parse.h"

namespace NetServer {

Parse::Parse(Data_Parse& data)
:data_parse_(data)
{

}

Parse::~Parse()
{
    
}

Data_Parse Parse::getParseData()
{
    return data_parse_;
}

}

