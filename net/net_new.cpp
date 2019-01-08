#include "net_new.h"

namespace USAF
ZONE_START

Net::Net()
{
    m_pConf = NULL;
    m_flagInit = false;
    cout << "Start USAF Net" << endl;
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





ZONE_END