#ifndef _INC_ACCEPTER_H
#define _INC_ACCEPTER_H
#include <memory>

#include "../inc/usaf_base.h"
#include "../thread/thread.h"
#include "session.h"
#include "fd_manager.h"
#include "tcp_recver.h"
#include "tcp_writer.h"
USAF_START

class Accepter : public Thread
{
public:
    Accepter(int nFd, FDManager* pFdManager);
    virtual ~Accepter();

    bool process();

private:

    int         m_nListenFd;
    FDManager*  m_pFdManager;
};
USAF_END

#endif

