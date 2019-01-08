#include "message.h"

namespace USAF
ZONE_START
Message::Message()
{
    m_pData = NULL;
    m_nLen = 0;
    m_pSession = NULL;
}

Message::Message(const char* pData, int nLen, spSessionInfo pSession)
{
    char* pTemp = new char[nLen];
    memcpy(pTemp, pData, nLen);
    m_pData = std::make_shared<char*>(pTemp);
    m_nLen = nLen;
    m_pSession = pSession;
}

Message::~Message()
{
    m_nLen = 0;
}

ostream& operator<< (ostream& stm, Message& ref)
{
    stm << "Message:" << *ref.m_pData <<" ["<< ref.getSessionInfo().getAddr() << "] [" << ref.getSessionInfo().getFd() << "]";
    return stm;
}





ZONE_END