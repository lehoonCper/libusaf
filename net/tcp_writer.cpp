#include "tcp_writer.h"
#include <unistd.h>
USAF_START

TcpWriter::TcpWriter(int nProcesserCnt)
{
    m_pMQ = TcpMessageQueueMgr::getInstance()->getWriteMessageQueue();
    m_nProcesserCnt = nProcesserCnt;
    m_pWriteTaskPool = new TaskPool(m_nProcesserCnt);
}

TcpWriter::~TcpWriter()
{
    stop();
    if(NULL != m_pWriteTaskPool)
    {
        delete m_pWriteTaskPool;
        m_pWriteTaskPool = NULL;
    }
}

bool TcpWriter::process()
{
    m_pWriteTaskPool->start();
    TCPMessage* pMsg = NULL;
    while(isRunning())
    {
        if(!m_pMQ->get(1, pMsg))
        {
            usleep(50);
            continue;
        }
        m_pWriteTaskPool->addTask(std::bind(&TcpWriter::writeTask, this, pMsg));
    }
    return true;
}

void TcpWriter::writeTask(TCPMessage* pMsg)
{
    if(pMsg == NULL || pMsg->size() <= 0)
    {
        return;
    }

    int nSendRet = send(pMsg->getSessionInfo()->getFd(), pMsg->getData(), pMsg->size(), MSG_NOSIGNAL);
    delete pMsg;
    if(nSendRet <= 0)
    {
        if(nSendRet == 0 || (EAGAIN != errno && EINPROGRESS != errno)) 
        {
            //disconnect(pMsg->getSessionInfo()->getFd());
        }
    }
}

/*
void TcpWriter::disconnect(int nFd)
{
    m_pFdManager->delSession(nFd, FDManager::EpollEventType::write_event);
}
*/

USAF_END