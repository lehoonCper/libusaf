#include "tcprecver.h"
USAF_START
TcpRecver::TcpRecver(FDManager* pFdManager)
{
    m_pMQ = TcpMessageQueue::getInstance();
    m_pFdManager = pFdManager;
    m_nReadFd = m_pFdManager->getReadFd();
    m_nEpollSize = m_pFdManager->getEpollSize();
    cout << "[EPOLL] readFd=" << m_nReadFd << " epollSize=" << m_nEpollSize << endl;
}

TcpRecver::~TcpRecver()
{


}

bool TcpRecver::process()
{
    struct epoll_event* pEvents = new epoll_event[m_nEpollSize];
    char* pBuffer = new char[TCPRECVER_BUFFER];
    while(isRunning())
    {
        doRecv(pEvents, pBuffer);
    }
}

void TcpRecver::doRecv(epoll_event * pEvent, char * pBuffer)
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
    //cout << "get read event, cnt=" << nActiveCnt << endl;

    int nRecvRet = 0;
    for (int i = 0; i < nActiveCnt; ++i)
    {
        nRecvRet = 0;
        memset(pBuffer, 0, TCPRECVER_BUFFER);
        int nFd = pEvent[i].data.fd;
        if(nFd < 0)
        {
            continue;
        }
        if((pEvent[i].events & (EPOLLHUP | EPOLLERR)) != 0)
        {
            //going to exit
            disconnect(nFd);
            //cout << "fd going to exit, fd=" << nFd << endl;
            continue;
        }
        if((pEvent[i].events & EPOLLIN) == 0)
        {
            continue;
        }

        do
        {
            nRecvRet = recv(nFd, pBuffer, TCPRECVER_BUFFER, MSG_NOSIGNAL);
        }
        while(-1 == nRecvRet && EINTR== errno);

        if(nRecvRet <= 0)
        {
             if(nRecvRet == 0 || (EAGAIN != errno && EINPROGRESS != errno)) 
             {
                //going to exit
                disconnect(nFd);
                //cout << "fd going to exit, fd=" << nFd << endl;
             }
            continue;
        }
       // cout << "get message: fd=" << nFd << " Message=" << pBuffer << endl;
        Message msg(pBuffer, nRecvRet, m_pFdManager->getSession(nFd));
        m_pMQ->put(nFd, msg);
    }

}

void TcpRecver::disconnect(int nFd)
{
    m_pFdManager->delSession(nFd);
}


USAF_END