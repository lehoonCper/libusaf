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
#include "tcp_message_queue_mgr.h"
#include "net_config.h"
#include "session.h"

USAF_START

class NetService : public Net
{
public:
    NetService();
    NetService(const NetConfigServer& conf);
    ~NetService();
   
    virtual bool start();
    virtual bool stop();

    void transPort(TCPMessage* pMsg);

    int response(TCPMessage* pMsg);


protected:
    virtual bool init();

private:
    int                 m_listenFd;
    NetConfigServer*    m_pConf;
    Accepter*           m_accepter;
    FDManager*          m_pFdManager;
    TcpRecver*          m_pTcpReader;
    TcpWriter*          m_pTcpWriter;
    TcpMessageQueueMgr* m_pMessageQueueMgr;
};


USAF_END
#endif