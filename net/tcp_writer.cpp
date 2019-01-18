#include "tcp_writer.h"
#include <unistd.h>
USAF_START

TcpWriter::TcpWriter(FDManager* pFdManager)
{
    m_pMQ = TcpMessageQueueMgr::getInstance()->getWriteMessageQueue();
    m_pFdManager = pFdManager;
    m_nWriteFd = m_pFdManager->getWriteFd();
    m_pFdManager->getEpollSize();
    std::cout << "[EPOLL] writeFd=" << m_nWriteFd << " epollSize=" << m_pFdManager->getEpollSize() << std::endl;
}

TcpWriter::~TcpWriter()
{


}

bool TcpWriter::process()
{
    struct epoll_event* pEvents = new epoll_event[m_pFdManager->getEpollSize()];
    while(isRunning())
    {
        if(m_pMQ && m_pFdManager)
        {
            doWirte(pEvents);
        }
        else
        {
            usleep(5000);
        }
    }
    delete pEvents;
}

void TcpWriter::doWirte(epoll_event* pEvent)
{
    int nActiveCnt = 0;
    do
    {
        nActiveCnt = epoll_wait(m_nWriteFd, pEvent, m_pFdManager->getEpollSize(), 50);
    }
    while(nActiveCnt == -1 && EINTR == errno);
    if(nActiveCnt <= 0)
    {
        return;
    }

    for (int i = 0; i < nActiveCnt; ++i)
    {
        int nFd = pEvent[i].data.fd;
        if(nFd < 0)
        {
            continue;
        }
        if((pEvent[i].events & (EPOLLHUP | EPOLLERR)) != 0)
        {
            disconnect(nFd);
            continue;
        }
        if((pEvent[i].events & EPOLLOUT) == 0)
        {
            continue;
        }

        TCPMessage* pMsg = NULL;
        if(!m_pMQ->get(nFd, pMsg))
        {
            continue;
        }
        if(pMsg->size() <= 0 || pMsg == NULL)
        {
            continue;
        }
        //std::cout << "data:" << pMsg->getData() << std::endl;
        int nSendRet = send(nFd, pMsg->getData(), pMsg->size(), MSG_NOSIGNAL);
        delete pMsg;
        if(nSendRet <= 0)
        {
            if(nSendRet == 0 || (EAGAIN != errno && EINPROGRESS != errno)) 
            {
                disconnect(nFd);
            }
        }
    }//for
}

void TcpWriter::disconnect(int nFd)
{
    m_pFdManager->delSession(nFd, FDManager::EpollEventType::write_event);
    //close(nFd);
}

USAF_END