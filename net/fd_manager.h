#ifndef FD_MANAGER_H
#define FD_MANAGER_H

#include <map>
#include <sys/epoll.h>

#include "../inc/usaf_base.h"
#include "session.h"
USAF_START

class FDManager
{
public:
    enum EpollEventType
    {
        read_event = 0,
        write_event = 1,
    };

    FDManager();
    ~FDManager();

    bool registeEpollEvent(int nFd, int nType);

    bool removeEpollEvent(int nFd, int nType);

    bool insertSession (int nFd, SessionInfo* pSession);

    SessionInfo* getSession(int nFd);

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

    std::map<int,SessionInfo*>   m_mpFds;
    int                 m_EpollFdRead;
    int                 m_EpollFdWrite;
    int                 m_nEpollSize;
 //add by lehoon: try c11 std::mutex in the future...
    pthread_mutex_t      m_mutexFds;
    pthread_mutex_t      m_mutexRdFd;
    pthread_mutex_t      m_mutexWtFd;

};





USAF_END

#endif