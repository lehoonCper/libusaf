#ifndef _INC_NET_BASE_H
#define _INC_NET_BASE_H
#include "../inc/usaf_base.h"
#include <sys/socket.h>
#include <netinet/in.h>

#include "netdef.h"
#include "netconfig.h"
USAF_START

class Net
{
public:
    Net();
    ~Net(){};

public:
    virtual bool start() = 0;
    virtual bool stop() = 0;

protected:
    virtual bool init() = 0;
protected:

    NetConfig*      m_pConf;
    sockaddr_in     m_addr;

    bool            m_flagInit;     //is init ready
};


USAF_END

#endif