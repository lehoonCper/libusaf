#ifndef _INC_TCP_MESSAGE_QUEUE_H
#define _INC_TCP_MESSAGE_QUEUE_H

#include "../container/message_queue.h"
#include "container/tcp_message.h"
USAF_START

typedef MessageQueue<TCPMessage*> TcpMessageQueue;
const int DEFAULT_MESSAGE_QUEUE_PROCESSER_CNT = 4;

class TcpMessageQueueMgr
{
public:
    enum MQ_TYPE
    {
        mq_type_read = 0,
        mq_type_wirte = 1,
    };

    static TcpMessageQueueMgr* getInstance()
    {
        if(!m_pInstance)
        {
            m_pInstance = new TcpMessageQueueMgr();
        }
        return m_pInstance;
    }

    TcpMessageQueue* getReadMessageQueue();
    TcpMessageQueue* getWriteMessageQueue();

    bool setProcesserCnt(int nType, int nProcesserCnt);

    static TcpMessageQueueMgr*  m_pInstance;
protected:
    TcpMessageQueueMgr();
    ~TcpMessageQueueMgr();

private:
    TcpMessageQueue*    m_pReadMessageQueue;
    TcpMessageQueue*    m_pWriteMessageQueue;
    int                 m_nReadProcesserCnt;
    int                 m_nWriteProcesserCnt;
};

USAF_END
#endif