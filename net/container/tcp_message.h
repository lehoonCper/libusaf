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
    TCPMessage(const char* pData, int nSize, spSessionInfo pSession);

    ~TCPMessage();

    spSessionInfo getSessionInfo();

private:
    spSessionInfo           m_pSession;
};

USAF_END
#endif