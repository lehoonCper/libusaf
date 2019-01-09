#ifndef _INC_TCPPROCESSER_H_
#define _INC_TCPPROCESSER_H_

#include "../inc/usaf_base.h"
#include "../thread/thread.h"
#include "container/tcp_message_queue.h"
#include "../container/message.h"
USAF_START
class TcpProcesser : public Thread
{
public:
    TcpProcesser(int nId, TcpMessageQueue* pMQ);
    ~TcpProcesser();

    bool process();

private:
    int                         m_nId;
    TcpMessageQueue*            m_pMQ;
};
USAF_END
#endif