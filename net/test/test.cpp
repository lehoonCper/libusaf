#include <thread>
#include <string>
#include <unistd.h>

#include "../../inc/usaf_base.h"
#include "../tcp_message_queue_mgr.h"
#include "../container/tcp_message.h"
#include "../../container/message.h"
#include "../net_service.h"

using namespace USAF;
extern int errno;
std::string res("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 4\r\nConnection: close\r\n\r\ntrue");

void func_send(void* p, int nHash)
{
    TcpMessageQueue* pReadMq = TcpMessageQueueMgr::getInstance()->getReadMessageQueue();
    NetService* pServ = (NetService*)p;
    TCPMessage* pRecvMsg;
    while(true)
    {
        if(pReadMq->get(nHash, pRecvMsg))
        {
            //std::cout << pRecvMsg->getData() << std::endl;
            TCPMessage* pSendMsg = new TCPMessage(res.data(), res.size(), pRecvMsg->getSessionInfo());
            //pServ->transPort(pSendMsg);
            send(pSendMsg->getSessionInfo()->getFd(), pSendMsg->getData(), pSendMsg->size(), MSG_NOSIGNAL);
            delete pRecvMsg;
        }
        else
        {
            usleep(50);
        }
    }
}

int main()
{
    NetConfigServer conf(8848, "localhost");
    NetService* pServ = new NetService(conf);
    if(false == pServ->start())
    {
        return -1;
    }
    
    std::thread* pt1 = new std::thread(func_send, (void*)pServ, 0);
    std::thread* pt2 = new std::thread(func_send, (void*)pServ, 1);
    std::thread* pt3 = new std::thread(func_send, (void*)pServ, 2);
    std::thread* pt4 = new std::thread(func_send, (void*)pServ, 3);    

    while(true)
    {
        usleep(5000);
    }

    return 0;
}