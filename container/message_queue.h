#ifndef _INC_MESSAGE_QUEUE_H
#define _INC_MESSAGE_QUEUE_H
#include "../inc/include.h"
#include "queue.h"

namespace USAF
ZONE_START

template <class T>
class MessageQueue
{
public:
    MessageQueue(int nCnt)
    {
        m_nHashCnt = nCnt;
        m_pHashMutex = new std::mutex[nCnt];
        for(int i = 0; i < nCnt; ++i)
        {
            m_mpMQ[i] = new Queue<T>;
        }
    }

    ~MessageQueue()
    {
        for(int i = 0; i < m_nHashCnt; i++)
        {
            m_pHashMutex[i].lock();
            auto iter = m_mpMQ.find(i);
            if(iter != m_mpMQ.end())
            {
                iter->second->clear();
                delete iter->second;
            }
            m_pHashMutex[i].unlock();
        }
        delete[] m_pHashMutex;
        m_nHashCnt = 0;
    }

    void put(int nId, const T& t)
    {
        int nHash = nId % m_nHashCnt;
        m_pHashMutex[nHash].lock();
        auto iter = m_mpMQ.find(nHash);
        if(iter != m_mpMQ.end())
        {
            iter->second->push(t);
        }
        m_pHashMutex[nHash].unlock();
    }

    bool get(int nId, T& t)
    {
        int nHash = nId % m_nHashCnt;
        m_pHashMutex[nHash].lock();
        auto iter = m_mpMQ.find(nHash);
        if(iter == m_mpMQ.end())
        {
            m_pHashMutex[nHash].unlock();
            return false;
        }
        if(iter->second->size() <= 0)
        {
            m_pHashMutex[nHash].unlock();
            return false;
        }
        bool ret = iter->second->pop(t);
        m_pHashMutex[nHash].unlock();
        return ret;
    }

private:
    std::map<int, Queue<T>*>        m_mpMQ;
    int                             m_nHashCnt;     //¹þÏ£Êý
    std::mutex*                     m_pHashMutex;   //¹þÏ£Ëø   
};
ZONE_END
#endif