#include "tcp_message_queue_mgr.h"
USAF_START
TcpMessageQueueMgr::TcpMessageQueueMgr()
{
    m_pReadMessageQueue = NULL;
    m_pWriteMessageQueue = NULL;
    m_nReadProcesserCnt = DEFAULT_MESSAGE_QUEUE_PROCESSER_CNT;
    m_nWriteProcesserCnt = DEFAULT_MESSAGE_QUEUE_PROCESSER_CNT;
}

TcpMessageQueueMgr::~TcpMessageQueueMgr()
{
    if(m_pReadMessageQueue != NULL)
    {
        delete m_pReadMessageQueue;
        m_pReadMessageQueue = NULL;
    }
    if(m_pWriteMessageQueue != NULL)
    {
        delete m_pWriteMessageQueue;
        m_pWriteMessageQueue = NULL;
    }
}

TcpMessageQueue* TcpMessageQueueMgr::getWriteMessageQueue()
{
    if(NULL == m_pWriteMessageQueue && m_nWriteProcesserCnt > 0)
    {
        m_pWriteMessageQueue = new TcpMessageQueue(m_nWriteProcesserCnt);
    }
    return m_pWriteMessageQueue;
}

TcpMessageQueue* TcpMessageQueueMgr::getReadMessageQueue()
{
    if(NULL == m_pReadMessageQueue && m_nReadProcesserCnt > 0)
    {
        m_pReadMessageQueue = new TcpMessageQueue(m_nReadProcesserCnt);
    }
    return m_pReadMessageQueue;
}

bool TcpMessageQueueMgr::setProcesserCnt(int nType, int nProcesserCnt)
{
    if(nType == mq_type_read && !m_pReadMessageQueue)
    {
        m_nReadProcesserCnt = nProcesserCnt;
    }
    else if (nType == mq_type_wirte && !m_pWriteMessageQueue) 
    {
        m_nWriteProcesserCnt = nProcesserCnt;
    }
    else
    {
        return false;
    }
    return true;
}


USAF_END