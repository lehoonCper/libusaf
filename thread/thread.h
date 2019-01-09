#ifndef _INC_THREAD_H
#define _INC_THREAD_H
#include <pthread.h>

#include "../inc/usaf_base.h"
USAF_START

typedef int thread_stat_t;

class Thread
{
public:
    Thread();

    virtual ~Thread(){}

    pthread_t start();

    bool stop();

    virtual bool process() = 0;

    bool isRunning() const;

    pthread_t getId() const;

private:
    pthread_t                m_nId;
    bool                     m_bRunning;
};

USAF_END
#endif