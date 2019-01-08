#include "../message.h"
#include "../../net/session.h"
using namespace USAF;

int main()
{
    char data[] = "this is a message for testing";
    int len = strlen(data);
    spSessionInfo s(new SessionInfo());
    Message msg(data, len, s);
    cout << "sourcemsg:" << msg << endl;
    Message msgcp = msg;
    cout << "cpmsg:" << msgcp << endl;

    return 0;
}