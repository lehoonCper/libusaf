#ifndef _INC_TCP_MESSAGE_QUEUE_H
#define _INC_TCP_MESSAGE_QUEUE_H
#include "../../container/message_queue.h"
#include "../../container/message.h"


namespace USAF
ZONE_START

#define TCP_MESSAGE_QUEUE_DEFAULT_HASH_NUM  4
class TcpMessageQueue : public MessageQueue<Message>
{
public:
    
    static TcpMessageQueue* getInstance(int nHash = TCP_MESSAGE_QUEUE_DEFAULT_HASH_NUM)
    {//Warning: 此处的hash在第一次实例化时生效
        if(!m_pInstance)
        {
            m_pInstance = new TcpMessageQueue(nHash);
        }
        return m_pInstance;
    }

protected:
    TcpMessageQueue(int nHash):MessageQueue<Message>(nHash)
    {

    }
    ~TcpMessageQueue()
    {
        if(m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = NULL;
        }
    }



private:
    static TcpMessageQueue* m_pInstance;
};

ZONE_END
#endif