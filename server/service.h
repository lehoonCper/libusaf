#ifndef _INC_NET_SERVICE_H_
#define _INC_NET_SERVICE_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <iostream>

#include <inc/usaf_base.h>
#include "service_conf.h"
#include "fd_manager.h"
USAF_START

class NetService
{
public:
    NetService(const NetConfigServer& conf);
    ~NetService();
   
    virtual bool start();
    virtual bool stop();

protected:
    virtual bool startNet();

private:
    bool                m_flagInit;
    int                 m_listenFd;
    NetConfigServer*    m_pConf;
    FDManager*          m_pFdManager;
};


USAF_END
#endif