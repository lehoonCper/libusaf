#ifndef _INC_QUEUE_H
#define _INC_QUEUE_H
#include <queue>
#include <mutex>
#include "../inc/usaf_base.h"
USAF_START

template <class T>
class Queue
{
public:
    Queue()
    {
        m_nSize = 0;
        m_pMutex = new std::mutex();
    }
    ~Queue()
    {
        if(NULL != m_pMutex)
        {
            delete m_pMutex;
            m_pMutex = NULL;
        }
    }

    void push(const T& t)
    {
       m_pMutex->lock();
       m_queue.push_back(t);
       ++m_nSize;
       m_pMutex->unlock();
    }

    bool pop(T& t)
    {
        m_pMutex->lock();
        if(m_queue.size() <= 0)
        {
            m_pMutex->unlock();
            return false;
        }
        t = m_queue.front();
        m_queue.pop_front();
        --m_nSize;
        m_pMutex->unlock();
        return true;
    }

    int size()
    {
        m_pMutex->lock();
        int ret = m_nSize;
        m_pMutex->unlock();
        return ret;
    }
    
    void clear()
    {
        m_pMutex->lock();
        m_queue.clear();
        m_nSize = 0;
        m_pMutex->unlock();
    }


private:
    std::mutex*          m_pMutex;
    std::deque<T>       m_queue;
    int                 m_nSize;
};
USAF_END
#endif