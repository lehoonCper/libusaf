#include "net_base.h"
USAF_START

Net::Net()
{
    m_flagInit = false;
    std::cout << "[service] start USAF Net" << std::endl;
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