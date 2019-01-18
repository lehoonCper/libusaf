#include "fd_manager.h"
#include <sys/types.h>
#include <utime.h>
#include <unistd.h>
#include <iostream>

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

bool FDManager::registeEpollEvent(int nFd, int nType)
{
    epoll_event ev;
    ev.data.fd = nFd;
    
    if(nType == FDManager::EpollEventType::read_event)
    {
        ev.events=EPOLLERR|EPOLLHUP|EPOLLIN;
        pthread_mutex_lock(&m_mutexRdFd);
        epoll_ctl(m_EpollFdRead, EPOLL_CTL_ADD, nFd, &ev);
        pthread_mutex_unlock(&m_mutexRdFd);
    }
    else if(nType == FDManager::EpollEventType::write_event)
    {
        ev.events=EPOLLERR|EPOLLHUP|EPOLLOUT;
        pthread_mutex_lock(&m_mutexWtFd);
        epoll_ctl(m_EpollFdWrite, EPOLL_CTL_ADD, nFd, &ev);
        pthread_mutex_unlock(&m_mutexWtFd);
    }
    else
    {
        return false;
    }
    return true;
}

bool FDManager::removeEpollEvent(int nFd, int nType)
{
    if(nType == FDManager::EpollEventType::read_event)
    {
        pthread_mutex_lock(&m_mutexRdFd);
        epoll_ctl(m_EpollFdRead, EPOLL_CTL_DEL, nFd, NULL);
        pthread_mutex_unlock(&m_mutexRdFd);
    }
    else if(nType == FDManager::EpollEventType::write_event)
    {
        pthread_mutex_lock(&m_mutexWtFd);
        epoll_ctl(m_EpollFdWrite, EPOLL_CTL_DEL, nFd, NULL);
        pthread_mutex_unlock(&m_mutexWtFd);
    }
    else
    {
        return false;
    }
    return true;
}

bool FDManager::insertSession (int nFd, SessionInfo* pSession)
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
//注册感兴趣的事件
    registeEpollEvent(nFd, FDManager::EpollEventType::read_event);
    return true;
}

SessionInfo* FDManager::getSession(int nFd)
{
    pthread_mutex_lock(&m_mutexFds);
    auto iter = m_mpFds.find(nFd);
    if(iter == m_mpFds.end())
    {
        printf("can't find fd, fd=%d\n", nFd);
        return nullptr;
    }
    SessionInfo* pSession = iter->second;
    pthread_mutex_unlock(&m_mutexFds);
    return pSession;
}

bool FDManager::delSession(int nFd, int nType)
{
//需要增加一个 等待close队列 解决time_wait问题??
    removeEpollEvent(nFd, nType);
    pthread_mutex_lock(&m_mutexFds);
    auto iter = m_mpFds.find(nFd);
    if(iter != m_mpFds.end())
    {
        //std::cout << "cost time: " << iter->second->getTimer()->getCostTimeMs() << std::endl;
        m_mpFds.erase(iter);
    }
    pthread_mutex_unlock(&m_mutexFds);
    close(nFd);
    return true;
}

USAF_END