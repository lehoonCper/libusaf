#include "net_base.h"
USAF_START

Net::Net()
{
    m_pConf = NULL;
    m_flagInit = false;
    printf("start USAF Net\n");
}

bool Net::init()
{
    return true;
}

bool Net::start()
{
    return true;   
}

bool Net::stop()
{
    return true;
}





USAF_END