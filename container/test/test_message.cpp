#include "../message.h"
using namespace USAF;

int main()
{
    char data[] = "this is a message for testing";
    int len = strlen(data);;
    Message msg(data, len);
    cout << "sourcemsg:" << msg << endl;
    Message msgcp = msg;
    cout << "cpmsg:" << msgcp << endl;

    return 0;
}