#ifndef _INC_MESSAGE_H_
#define _INC_MESSAGE_H_
#include "../inc/include.h"
#include "../net/session.h"
USAF_START

typedef std::shared_ptr<char*>  spchar;
class Message
{
public:
    Message();
    Message(const char* pData, int nLen, spSessionInfo pSession);
    virtual ~Message();

    friend ostream& operator <<(ostream& stream, Message& ref);

    Message& operator = (Message& ref)
    {
        this->m_pData = ref.m_pData;
        this->m_nLen = ref.m_nLen;
        this->m_pSession = ref.m_pSession;
        return *this;
    }

//inline
    inline char* getData() const
    {
        return *m_pData;
    }

    inline int size() const
    {
        return m_nLen;
    }

    inline SessionInfo getSessionInfo() const
    {
        return *m_pSession;
    }

private:

    spchar          m_pData;
    int             m_nLen;
    spSessionInfo   m_pSession;
};
USAF_END
#endif