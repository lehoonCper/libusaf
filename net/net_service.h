#pragma once
#include "net_new.h"
#include "accepter.h"
namespace USAF
ZONE_START

class NetService : public Net
{
public:
    NetService();
    NetService(const NetConfigServer& conf);


   
    virtual bool start();
    virtual bool stop();

protected:
    virtual bool init();

private:
    int                 m_listenFd;
    Accepter*           m_accepter;
    
};


ZONE_END