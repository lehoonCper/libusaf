#ifndef _INC_QUEUE_H
#define _INC_QUEUE_H
#include "../inc/include.h"

namespace USAF
ZONE_START

template <class T>
class Queue
{
public:
    Queue()
    {
        m_nSize = 0;
    }
    ~Queue()
    {

    }

    void push(const T& t)
    {
       m_mutex.lock();
       m_queue.push_back(t);
       ++m_nSize;
       m_mutex.unlock();
    }

    bool pop(T& t)
    {
        m_mutex.lock();
        if(0 == m_queue.size())
        {
            m_mutex.unlock();
            return false;
        }
        t = m_queue.front();
        m_queue.pop_front();
        --m_nSize;
        m_mutex.unlock();
        return true;
    }

    int size()
    {
        m_mutex.lock();
        int ret = m_nSize;
        m_mutex.unlock();
        return ret;
    }
    
    void clear()
    {
        m_mutex.lock();
        m_queue.clear();
        m_nSize = 0;
        m_mutex.unlock();
    }


private:
    std::mutex          m_mutex;
    std::deque<T>       m_queue;
    int                 m_nSize;
};
ZONE_END
#endif