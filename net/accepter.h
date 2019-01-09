#ifndef _INC_ACCEPTER_H
#define _INC_ACCEPTER_H
#include <memory>

#include "../inc/usaf_base.h"
#include "../thread/thread.h"
#include "session.h"
#include "fd_manager.h"
#include "tcprecver.h"
USAF_START

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
USAF_END

#endif

