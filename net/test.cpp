#include "../inc/include.h"
#include "container/tcp_message_queue.h"
#include "../container/message.h"
#include <thread>
#include "net_service.h"

using namespace USAF;
extern int errno;

string res("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 4\r\nConnection: close\r\n\r\ntrue");
void func_send(void* p, int nHash)
{
    TcpMessageQueue* mq = (TcpMessageQueue*)p;
    Message msg;
    while(true)
    {
        if(mq->get(nHash, msg))
        {
            send(msg.getSessionInfo().getFd(), res.data(), res.size(), MSG_NOSIGNAL);
        }
        else
        {
            usleep(5000);
        }
    }
}

int main()
{
    NetConfigServer conf(8848, "localhost");
    NetService serv(conf);
    TcpMessageQueue* mq = TcpMessageQueue::getInstance(4);
    serv.start();
    
    std::thread* pt1 = new std::thread(func_send, (void*)mq, 0);
    std::thread* pt2 = new std::thread(func_send, (void*)mq, 1);
    std::thread* pt3 = new std::thread(func_send, (void*)mq, 2);
    std::thread* pt4 = new std::thread(func_send, (void*)mq, 3);    

    while(true)
    {
        usleep(5000);
    }

    return 0;
}