#include "tcp_processer.h"
USAF_START
TcpProcesser::TcpProcesser(int nId)
{
    m_nId = nId;
    m_pMessageQueueMgr = TcpMessageQueueMgr::getInstance();
}

TcpProcesser::~TcpProcesser()
{
    m_pMessageQueueMgr = NULL;
}

bool TcpProcesser::process()
{
    if(!m_pMessageQueueMgr)
    {
        return false;
    }
    TcpMessageQueue* pMessageQueueRead = m_pMessageQueueMgr->getReadMessageQueue();
    if(pMessageQueueRead)
    {
        return false;
    }
    while(isRunning())
    {
        TCPMessage* pMsg = NULL;
        if(!pMessageQueueRead->get(m_nId, pMsg))
        {
            continue;
        }
        std::cout << pMsg << std::endl;
        if(pMsg)
        {
            delete pMsg;
        }
    }
}

USAF_END