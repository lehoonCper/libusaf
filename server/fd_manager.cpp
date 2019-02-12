#include <sys/types.h>
#include <utime.h>
#include <unistd.h>
#include <iostream>
#include "fd_manager.h"

USAF_START
FDManager::FDManager(int nListenFd)
{
    m_nListenFd = nListenFd;
    m_nEpollSize = 65533;
    m_EpollFdRead = epoll_create(m_nEpollSize);
    m_EpollFdWrite = epoll_create(m_nEpollSize);
    m_pMutexFds = new std::mutex();
    m_pMutexRdFd = new std::mutex();
    m_pMutexWtFd = new std::mutex();
}

FDManager::~FDManager()
{
    if(NULL != m_pMutexFds)
    {
        delete m_pMutexFds;
        m_pMutexFds = NULL;
    }
    if(NULL != m_pMutexRdFd)
    {
        delete m_pMutexRdFd;
        m_pMutexRdFd = NULL;
    }
    if(NULL != m_pMutexWtFd)
    {
        delete m_pMutexWtFd;
        m_pMutexWtFd = NULL;
    }
}

bool FDManager::process()
{
    while(isRunning())
    {
        int nFd = accept(m_nListenFd, NULL, NULL);
        if (nFd == -1)
        {
            continue;
        }
        NetInfo* pInfo = new NetInfo();
        pInfo->setNetInfo(nFd);
        insertSession(nFd, pInfo);
        std::cout << "set 1" << std::endl;
    }
    return true;
}

bool FDManager::registeEpollEvent(int nFd, int nType)
{
    epoll_event ev;
    ev.data.fd = nFd;
    
    if(nType == FDManager::EpollEventType::read_event)
    {
        ev.events=EPOLLERR|EPOLLHUP|EPOLLIN;
        m_pMutexRdFd->lock();
        epoll_ctl(m_EpollFdRead, EPOLL_CTL_ADD, nFd, &ev);
        m_pMutexRdFd->unlock();
    }
    else if(nType == FDManager::EpollEventType::write_event)
    {
        ev.events=EPOLLERR|EPOLLHUP|EPOLLOUT;
        m_pMutexWtFd->lock();
        epoll_ctl(m_EpollFdWrite, EPOLL_CTL_ADD, nFd, &ev);
        m_pMutexWtFd->unlock();
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
        m_pMutexRdFd->lock();
        epoll_ctl(m_EpollFdRead, EPOLL_CTL_DEL, nFd, NULL);
        m_pMutexRdFd->unlock();
    }
    else if(nType == FDManager::EpollEventType::write_event)
    {
        m_pMutexWtFd->lock();
        epoll_ctl(m_EpollFdWrite, EPOLL_CTL_DEL, nFd, NULL);
        m_pMutexWtFd->unlock();
    }
    else
    {
        return false;
    }
    return true;
}

bool FDManager::insertSession (int nFd, NetInfo* pInfo)
{
    m_pMutexFds->lock();
    auto iter = m_mpFds.find(nFd);
    if(iter != m_mpFds.end())
    {
        m_pMutexFds->lock();
        printf("fd already exist, fd=%d\n", nFd);
        return false;
    }
    m_mpFds[nFd] = pInfo;
    m_pMutexFds->unlock();
    registeEpollEvent(nFd, FDManager::EpollEventType::read_event);
    return true;
}

NetInfo* FDManager::getSession(int nFd)
{
    m_pMutexFds->lock();
    auto iter = m_mpFds.find(nFd);
    if(iter == m_mpFds.end())
    {
        printf("can't find fd, fd=%d\n", nFd);
        return nullptr;
    }
    NetInfo* pInfo = iter->second;
    m_pMutexFds->unlock();
    return pInfo;
}

bool FDManager::delSession(int nFd, int nType)
{
//需要增加一个 等待close队列 解决time_wait问题??
    removeEpollEvent(nFd, nType);
    m_pMutexFds->lock();
    auto iter = m_mpFds.find(nFd);
    if(iter != m_mpFds.end())
    {
        //std::cout << "cost time: " << iter->second->getTimer()->getCostTimeMs() << std::endl;
        delete iter->second;
        m_mpFds.erase(iter);
    }
    m_pMutexFds->unlock();
    close(nFd);
    return true;
}

USAF_END