#include "../tcp_message_queue.h"

using namespace USAF;

int main()
{
    char data[] = "this is a message for testing";
    int len = strlen(data);
    spSessionInfo s(new SessionInfo());
    Message msg(data, len, s);
    
    TcpMessageQueue* p = TcpMessageQueue::getInstance(10);
    for(int i =0; i< 100; i++)
    {
        p->put(i,msg);
    }

    Message ret ;
    while(p->get(0,ret))
    {
        cout << ret << endl;
    }

    return 0;
}