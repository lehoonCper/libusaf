#ifndef _INC_THREAD_H
#define _INC_THREAD_H
#include <thread>
#include "../inc/usaf_base.h"
USAF_START

class Thread
{
public:
    Thread();
    virtual ~Thread();

    bool start();
    bool stop();
    virtual bool process() = 0;

    inline bool isRunning() const
    {
        return m_bRunning;
    }


private:
    std::thread*        m_pThread;
    bool                m_bRunning;
};

USAF_END
#endif