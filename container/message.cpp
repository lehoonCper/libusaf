#include "message.h"

USAF_START

Message::Message()
{
    m_pData = new char[MESSAGE_DEFAULT_SIZE];
    memset(m_pData, 0, MESSAGE_DEFAULT_SIZE);
    m_nSize = MESSAGE_DEFAULT_SIZE;
}

Message::Message(const char* pData, int nSize)
{
    m_pData = new char[nSize];
    memcpy(m_pData, pData, nSize);
    m_nSize = nSize;
}

Message::Message(const Message& ref)
{
    m_pData = new char[ref.size()];
    memcpy(m_pData, ref.getData(), ref.size());
    m_nSize = ref.size();
}

Message::~Message()
{
    m_nSize = 0;
    if(m_pData)
    {
        delete[] m_pData;
        m_pData = NULL;
    }
}

std::ostream& operator<< (std::ostream& stm, Message& ref)
{
    stm << "Message:" << ref.getData() << "length: " << ref.size() << std::endl;
    return stm;
}



USAF_END