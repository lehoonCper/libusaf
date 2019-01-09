#ifndef _INC_NET_SERVICE_H
#define _INC_NET_SERVICE_H

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

#include "../inc/usaf_base.h"
#include "net_base.h"
#include "accepter.h"
USAF_START

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


USAF_END
#endif