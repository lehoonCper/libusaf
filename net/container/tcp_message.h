#ifndef _INC_TCP_MESSAGE_H_
#define _INC_TCP_MESSAGE_H_

#include "../../container/message.h"
#include "../session.h"
USAF_START

class TCPMessage : public Message
{
public:
    TCPMessage();
    TCPMessage(const TCPMessage& ref);
    TCPMessage(const char* pData, int nSize, SessionInfo* pSession);

    ~TCPMessage();

    SessionInfo*    getSessionInfo();

private:
    SessionInfo*     m_pSession;
};

USAF_END
#endif