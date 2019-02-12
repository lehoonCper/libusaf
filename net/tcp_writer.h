#ifndef _INC_TCP_WRITER_H
#define _INC_TCP_WRITER_H

#include <vector>
#include "../inc/usaf_base.h"
#include "fd_manager.h"
#include "../thread/thread.h"
#include "tcp_message_queue_mgr.h"
USAF_START

class TcpWriter : public Thread
{
public:
    TcpWriter(int nProcesserCnt = 4);
    virtual ~TcpWriter();

    virtual bool process();

    //void disconnect(int nFd);

    void writeTask(TCPMessage* pMsg);

private:
    int                 m_nWriteFd;
    int                 m_nProcesserCnt;
    TaskPool*           m_pWriteTaskPool;
    TcpMessageQueue*    m_pMQ;
};

USAF_END
#endif