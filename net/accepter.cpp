#include "accepter.h"
USAF_START

Accepter::Accepter(int nFd, FDManager* pFdManager)
{
    m_nListenFd = nFd;
    m_pFdManager = pFdManager;
}

Accepter::~Accepter()
{
    if(isRunning())
    {
        stop();
    }
}

bool Accepter::process()
{
    while(isRunning())
    {
        int nFd = accept(m_nListenFd, NULL, NULL);
        if (nFd == -1)
        {
            continue;
        }
        SessionInfo* pSession = new SessionInfo();
        pSession->setSession(nFd);
        m_pFdManager->insertSession(nFd, pSession);
    }
}



USAF_END