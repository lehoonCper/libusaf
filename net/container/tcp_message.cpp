#include "tcp_message.h"
USAF_START

TCPMessage::TCPMessage()
{
    m_pSession = NULL;
}

TCPMessage::TCPMessage(const TCPMessage& ref) : Message(ref)
{
    m_pSession = new SessionInfo();
    memcpy(m_pSession, ref.m_pSession, sizeof(SessionInfo));
}

TCPMessage::TCPMessage(const char * pData, int nSize, SessionInfo* pSession):Message(pData, nSize)
{
    m_pSession = new SessionInfo(pSession);
}

TCPMessage::~TCPMessage()
{
    if(NULL != m_pSession)
    {
        delete m_pSession;
    }
}

SessionInfo* TCPMessage::getSessionInfo()
{
    return m_pSession;
}

USAF_END