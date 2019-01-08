#include "tcpprocesser.h"
namespace USAF
ZONE_START
TcpMessageQueue* TcpMessageQueue::m_pInstance = NULL;
TcpProcesser::TcpProcesser(int nId, TcpMessageQueue * pMQ)
{
    m_nId = nId;
    m_pMQ = pMQ;
}

TcpProcesser::~TcpProcesser()
{
    m_pMQ = NULL;
}

bool TcpProcesser::process()
{
    while(isRunning())
    {
        Message msg;
        if(!m_pMQ->get(m_nId, msg))
        {
            continue;
        }

        cout << msg << endl;
    }

}

ZONE_END