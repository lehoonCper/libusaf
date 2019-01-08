#include "thread.h"
namespace USAF
ZONE_START


void* thread_caller(void* p)
{
    if(p)
    {
        Thread* pThis = (Thread*) p;
        pThis->process();
    }
    return p;
}

Thread::Thread()
{
    m_nId = -1;
    m_bRunning = false;
}

pthread_t Thread::start()
{
    if(isRunning())
    {
        return -1;
    }

    m_bRunning = true;
    pthread_create(&m_nId, NULL, thread_caller, this);
    if(m_nId <= 0)
    {
       return -1;
    }
    //what about pthread_join()?
    pthread_detach(m_nId);  
    return m_nId;
}

bool Thread::stop()
{
    m_bRunning = false;
    return true;
}

bool Thread::process()
{
    while(isRunning())
    {
        cout << "Thread::Process" << endl;
        usleep(500000);
    }
    return true;
}

bool Thread::isRunning() const
{
    return m_bRunning;
}

pthread_t Thread::getId() const
{
    return m_nId;
}



ZONE_END