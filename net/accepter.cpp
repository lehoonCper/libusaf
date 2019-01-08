#include "accepter.h"

namespace USAF
ZONE_START

Accepter::Accepter(int nFd)
{
    m_nListenFd = nFd;
    m_pFdManager = new FDManager();
    m_pTcpReader = new TcpRecver(m_pFdManager);
    m_pTcpReader->start();
}

Accepter::~Accepter()
{
    if(m_pFdManager)
    {
        delete m_pFdManager;
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

        //cout << "recv new fd: " << nFd << endl;
        spSessionInfo session(new SessionInfo());
        session->setSession(nFd);
        m_pFdManager->insertSession(nFd, session);
    }
}



ZONE_END