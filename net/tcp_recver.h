#ifndef INC_TCPRECVER_H
#define INC_TCPRECVER_H

#include "../inc/usaf_base.h"
#include "fd_manager.h"
#include "../thread/thread.h"
#include "tcp_message_queue_mgr.h"
#include "../container/buffer.h"
USAF_START

class TcpRecver : public Thread
{
public:
    TcpRecver(FDManager* pFdManager, int nRecvThreadCnt = 1);
    virtual ~TcpRecver();

    virtual bool process();

    void pollRead(epoll_event* pEvent);

    void recvTask(int nId, int nEvent);

    void disconnect(int nFd);

private:
    int                 m_nReadFd;
    int                 m_nEpollSize;
    int                 m_nRecvThreadCnt;
    FDManager*          m_pFdManager;
    TcpMessageQueue*    m_pMQ;
    TaskPool*           m_pRecvTaskPool;
    BufferPool*         m_pBufferPool;
};

#define TCPRECVER_BUFFER    10000

USAF_END
#endif