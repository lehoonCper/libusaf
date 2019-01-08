#pragma once
#include "../inc/include.h"

namespace USAF
ZONE_START

typedef int thread_stat_t;


class Thread
{
public:
    Thread();

    virtual ~Thread(){}

    pthread_t start();

    bool stop();

    virtual bool process();

    bool isRunning() const;

    pthread_t getId() const;

private:
    pthread_t                m_nId;
    bool                     m_bRunning;
};

ZONE_END