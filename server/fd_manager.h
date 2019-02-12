#ifndef FD_MANAGER_H
#define FD_MANAGER_H

#include <map>
#include <sys/epoll.h>
#include <mutex>
#include <inc/usaf_base.h>
#include <thread/thread.h>
#include "net_info.h"
USAF_START

class FDManager : public Thread
{
public:
    enum EpollEventType
    {
        read_event = 0,
        write_event = 1,
    };

    FDManager(int nListenFd);
    ~FDManager();

    bool process();

    bool registeEpollEvent(int nFd, int nType);
    bool removeEpollEvent(int nFd, int nType);

    bool insertSession (int nFd, NetInfo* pInfo);
    NetInfo* getSession(int nFd);
    bool delSession(int nFd, int nType);

    int getReadFd() const
    {
        return m_EpollFdRead;
    }

    int getWriteFd() const
    {
        return m_EpollFdWrite;
    }

    int getEpollSize() const
    {
        return m_nEpollSize;
    }

private:
    int                 m_nListenFd;
    int                 m_EpollFdRead;
    int                 m_EpollFdWrite;
    int                 m_nEpollSize;
    std::mutex*         m_pMutexFds;
    std::mutex*         m_pMutexRdFd;
    std::mutex*         m_pMutexWtFd;
    std::map<int, NetInfo*>   m_mpFds;
};

USAF_END
#endif