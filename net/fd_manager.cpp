#include "fd_manager.h"
USAF_START

FDManager::FDManager()
{
    m_nEpollSize = 65533;
    m_EpollFdRead = epoll_create(m_nEpollSize);
    m_EpollFdWrite = epoll_create(m_nEpollSize);
    pthread_mutex_init(&m_mutexFds, NULL); 
    pthread_mutex_init(&m_mutexRdFd, NULL); 
    pthread_mutex_init(&m_mutexWtFd, NULL); 
}

FDManager::~FDManager()
{


}

bool FDManager::insertSession (int nFd, spSessionInfo pSession)
{
    pthread_mutex_lock(&m_mutexFds);
    auto iter = m_mpFds.find(nFd);
    if(iter != m_mpFds.end())
    {
        pthread_mutex_unlock(&m_mutexFds);
        printf("fd already exist, fd=%d\n", nFd);
        return false;
    }
    m_mpFds[nFd] = pSession;
    pthread_mutex_unlock(&m_mutexFds);

//注册对读时间感兴趣
    epoll_event ev;
    ev.data.fd = nFd;
    ev.events=EPOLLERR|EPOLLHUP|EPOLLIN;

    pthread_mutex_lock(&m_mutexRdFd);
    epoll_ctl(m_EpollFdRead, EPOLL_CTL_ADD, nFd, &ev);
    pthread_mutex_unlock(&m_mutexRdFd);
 //   cout << "insert fd ok: fd=" << nFd << endl;
    
    return true;
}

spSessionInfo FDManager::getSession(int nFd)
{
    pthread_mutex_lock(&m_mutexFds);
    auto iter = m_mpFds.find(nFd);
    if(iter == m_mpFds.end())
    {
        printf("can't find fd, fd=%d\n", nFd);
        return nullptr;
    }
    spSessionInfo pDtl = iter->second;
    pthread_mutex_unlock(&m_mutexFds);
    return pDtl;
}

bool FDManager::delSession(int nFd)
{
//需要增加一个 等待close队列 解决time_wait问题
    pthread_mutex_lock(&m_mutexRdFd);
    epoll_ctl(m_EpollFdRead, EPOLL_CTL_DEL, nFd, NULL);
    pthread_mutex_unlock(&m_mutexRdFd);

    pthread_mutex_lock(&m_mutexFds);
    auto iter = m_mpFds.find(nFd);
    if(iter != m_mpFds.end())
    {
        m_mpFds.erase(iter);
    }
    close(nFd);
    pthread_mutex_unlock(&m_mutexFds);

    return true;
}

USAF_END