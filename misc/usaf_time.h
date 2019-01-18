#ifndef _INC_TIME_H
#define _INC_TIME_H

#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "../inc/usaf_base.h"
USAF_START

class Timer
{
public:
    Timer()
    {
        m_pTimeVal = new timeval();
        gettimeofday(m_pTimeVal, NULL);
    }

    ~Timer()
    {
        if(m_pTimeVal)
        {
            delete m_pTimeVal;
            m_pTimeVal = NULL;
        }
    }

    inline long getTime() const
    {
        return m_pTimeVal->tv_sec;
    }

    inline long getTimeMs() const
    {
        return m_pTimeVal->tv_sec * 1000 + m_pTimeVal->tv_usec / 1000;
    }

    inline long getCostTime() const
    {
        struct timeval timeNow;
        gettimeofday(&timeNow, NULL);
        return timeNow.tv_sec - getTime();
    }

    inline long getCostTimeMs() const
    {
        struct timeval timeNow;
        gettimeofday(&timeNow, NULL);
        return timeNow.tv_sec * 1000 + timeNow.tv_usec / 1000 - getTimeMs();
    }

    void resetTime()
    {
        gettimeofday(m_pTimeVal, NULL);
    }

    void copy(Timer* pTimer)
    {
        if(!pTimer || !this)
        {
            return;
        }
        memcpy(m_pTimeVal, pTimer->m_pTimeVal, sizeof(timeval));
    }
    
private:
    timeval* m_pTimeVal;
};

USAF_END
#endif