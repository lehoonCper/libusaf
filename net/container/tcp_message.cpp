#include "tcp_message.h"
USAF_START

TCPMessage::TCPMessage()
{
    m_pSession = NULL;
}

TCPMessage::TCPMessage(const TCPMessage& ref) : Message(ref)
{
    m_pSession = ref.m_pSession;
}

TCPMessage::TCPMessage(const char * pData, int nSize, spSessionInfo pSession):Message(pData, nSize)
{
    m_pSession = pSession;
}

TCPMessage::~TCPMessage()
{

}

spSessionInfo TCPMessage::getSessionInfo()
{
    return m_pSession;
}

USAF_END