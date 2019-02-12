#include "thread.h"
USAF_START

Thread::Thread()
{
    m_pThread = NULL;
    m_bRunning = false;
}

Thread::~Thread()
{
    if(NULL != m_pThread)
    {
        delete m_pThread;
        m_pThread = NULL;
    }
}

bool Thread::start()
{
    if(true == m_bRunning || NULL != m_pThread)
    {
        return false;
    }

    m_pThread = new std::thread(std::bind(&Thread::process, this));
    if(NULL == m_pThread)
    {
        return false;
    }

    m_bRunning = true;
    return true;
}

bool Thread::stop()
{
    if(false == m_bRunning)
    {
        return false;
    }
    m_bRunning = false;
    m_pThread->join();
    return true;
}

USAF_END
