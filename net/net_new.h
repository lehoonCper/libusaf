#pragma once
#include "../inc/include.h"
#include "netdef.h"
#include "netconfig.h"

namespace USAF
ZONE_START

class Net
{
public:
    Net();
    ~Net(){};

public:
    virtual bool start();
    virtual bool stop();

protected:
    virtual bool init();
protected:

    NetConfig*      m_pConf;        //net config
    sockaddr_in     m_addr;         

    bool            m_flagInit;
};


ZONE_END