#ifndef _INC_TCP_WRITER_H
#define _INC_TCP_WRITER_H

#include "../inc/usaf_base.h"
#include "fd_manager.h"
#include "../thread/thread.h"
#include "tcp_message_queue_mgr.h"
USAF_START

class TcpWriter : public Thread
{
public:
    TcpWriter(FDManager* pFdManager);
    virtual ~TcpWriter();

    virtual bool process();

    void doWirte(epoll_event* pEvent);

    void disconnect(int nFd);

private:
    int                 m_nWriteFd;             //epoll write fd
    FDManager*          m_pFdManager;           //all accepted fd
    TcpMessageQueue*    m_pMQ;                  //msg queue
};

USAF_END
#endif