#include "tcp_recver.h"
#include <unistd.h>
USAF_START
BufferPool* BufferPool::m_pInstance = NULL;
TcpRecver::TcpRecver(FDManager* pFdManager, int nRecvThreadCnt)
{
    m_nRecvThreadCnt = nRecvThreadCnt;
    m_pRecvTaskPool = new TaskPool(m_nRecvThreadCnt);
    m_pBufferPool = BufferPool::getInstance();

    m_pMQ = TcpMessageQueueMgr::getInstance()->getReadMessageQueue();
    m_pFdManager = pFdManager;
    m_nReadFd = m_pFdManager->getReadFd();
    m_nEpollSize = m_pFdManager->getEpollSize();
    std::cout << "[EPOLL] readFd=" << m_nReadFd << " epollSize=" << m_nEpollSize << std::endl;
}   

TcpRecver::~TcpRecver()
{
    stop();
    if(NULL != m_pRecvTaskPool)
    {
        delete m_pRecvTaskPool;
    }
}

bool TcpRecver::process()
{
    struct epoll_event* pEvents = new epoll_event[m_nEpollSize];
	m_pRecvTaskPool->start();
    while(isRunning())
    {
        pollRead(pEvents);
    }
    delete[] pEvents;
    return true;
}

void TcpRecver::pollRead(epoll_event * pEvent)
{
    int nActiveCnt = 0;
    do
    {
        nActiveCnt = epoll_wait(m_nReadFd, pEvent, m_nEpollSize, 50);
    }
    while(nActiveCnt == -1 && EINTR == errno);
    if(nActiveCnt <= 0)
    {
        return;
    }
    for (int i = 0; i < nActiveCnt; ++i)
    {
        //m_pRecvTaskPool->addTask(std::bind(&TcpRecver::recvTask, this, (int)(pEvent[i].data.fd), (int)(pEvent[i].events)));
        recvTask((int)(pEvent[i].data.fd), (int)(pEvent[i].events));
    }
}

void TcpRecver::recvTask(int nFd, int nEvent)
{
    int nRecvRet = 0;
    if(nFd < 0)
    {
        return;
    }
    if((nEvent & (EPOLLHUP | EPOLLERR)) != 0)
    {
        disconnect(nFd);
        return;
    }
    if((nEvent & EPOLLIN) == 0)
    {
        return;
    }

    Buffer* pBuffer = m_pBufferPool->invoke();
    memset(pBuffer->getData(), 0, TCPRECVER_BUFFER);
    do
    {
        nRecvRet = recv(nFd, pBuffer->getData(), TCPRECVER_BUFFER, MSG_NOSIGNAL);
    }
    while(-1 == nRecvRet && EINTR== errno);

    //printf("recv cnt: %d\n", nRecvRet);

    if(nRecvRet <= 0)
    {
        if(nRecvRet == 0 || (EAGAIN != errno && EINPROGRESS != errno)) 
        {
            disconnect(nFd);
        }
        m_pBufferPool->release(pBuffer);
        return;
    }
    TCPMessage* pMsg = new TCPMessage(pBuffer->getData(), nRecvRet, m_pFdManager->getSession(nFd));
    m_pMQ->put(nFd, pMsg);
    m_pBufferPool->release(pBuffer);
}

void TcpRecver::disconnect(int nFd)
{
    m_pFdManager->delSession(nFd, FDManager::EpollEventType::read_event);
}

USAF_END