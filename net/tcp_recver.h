#ifndef INC_TCPRECVER_H
#define INC_TCPRECVER_H

#include "../inc/usaf_base.h"
#include "fd_manager.h"
#include "../thread/thread.h"
#include "tcp_message_queue_mgr.h"
USAF_START

class TcpRecver : public Thread
{
public:
    TcpRecver(FDManager* pFdManager);
    virtual ~TcpRecver();

    virtual bool process();

    void doRecv(epoll_event* pEvent, char* pBuffer);

    void disconnect(int nFd);

private:
    int                 m_nReadFd;              //epoll read fd
    int                 m_nEpollSize;           //epoll list size
    FDManager*          m_pFdManager;           //all accepted fd
    TcpMessageQueue*    m_pMQ;          //msg queue
};

#define TCPRECVER_BUFFER    10000

USAF_END
#endif