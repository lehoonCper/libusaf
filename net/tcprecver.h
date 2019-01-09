#ifndef INC_TCPRECVER_H
#define INC_TCPRECVER_H

#include "../inc/usaf_base.h"
#include "fd_manager.h"
#include "../thread/thread.h"
#include "container/tcp_message_queue.h"
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
    int         m_nReadFd;
    int         m_nEpollSize;
    FDManager*  m_pFdManager;
    TcpMessageQueue*    m_pMQ;
};

#define TCPRECVER_BUFFER    10000

USAF_END
#endif