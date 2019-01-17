#ifndef _INC_TCPPROCESSER_H_
#define _INC_TCPPROCESSER_H_

#include "../inc/usaf_base.h"
#include "../thread/thread.h"
#include "tcp_message_queue_mgr.h"
#include "container/tcp_message.h"
USAF_START
class TcpProcesser : public Thread
{
public:
    TcpProcesser(int nId);
    ~TcpProcesser();

    bool process();

private:
    int                         m_nId;
    TcpMessageQueueMgr*         m_pMessageQueueMgr;
};
USAF_END
#endif