#ifndef _INC_MESSAGE_H_
#define _INC_MESSAGE_H_
#include <iostream>
#include <string.h>
#include "../misc/usaf_time.h"
USAF_START

#define MESSAGE_DEFAULT_SIZE        1
class Message
{
public:
    Message();
    Message(const Message& ref);
    Message(const char* pData, int nSize);
    virtual ~Message();

    friend std::ostream& operator <<(std::ostream& stream, Message& ref);

    Message& operator = (Message& ref)
    {
        if(size() != ref.size())
        {
            delete m_pData;
            m_pData = new char[ref.size()];
        }
        memcpy(this->m_pData, ref.m_pData, ref.size());
        this->m_nSize = ref.m_nSize;
        this->m_pTime->resetTime();

        return *this;
    }

//inline
    inline char* getData() const
    {
        return m_pData;
    }

    inline int size() const
    {
        return m_nSize;
    }

    inline Timer* getTime() const
    {
        return m_pTime;
    }

private:
    char*          m_pData;
    size_t         m_nSize;
    Timer*         m_pTime;
};
USAF_END
#endif