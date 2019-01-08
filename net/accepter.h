#pragma once
#include "../thread/thread.h"
#include "session.h"
#include "fd_manager.h"
#include "tcprecver.h"
#include <memory>

namespace USAF
ZONE_START

class Accepter : public Thread
{
public:
    Accepter(int nFd);
    ~Accepter();

    bool process();

private:

    int         m_nListenFd;
    FDManager*  m_pFdManager;
    TcpRecver*  m_pTcpReader;
};







ZONE_END

