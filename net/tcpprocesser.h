#ifndef _INC_TCPPROCESSER_H_
#define _INC_TCPPROCESSER_H_
#include "../inc/include.h"
#include "../thread/thread.h"
#include "container/tcp_message_queue.h"
#include "../container/message.h"
namespace USAF
ZONE_START
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
ZONE_END
#endif