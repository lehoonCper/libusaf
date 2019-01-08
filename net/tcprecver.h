#ifndef INC_TCPRECVER_H
#define INC_TCPRECVER_H
#include "fd_manager.h"
#include "../inc/include.h"
#include "../thread/thread.h"
#include "container/tcp_message_queue.h"
namespace USAF
ZONE_START

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

ZONE_END
#endif