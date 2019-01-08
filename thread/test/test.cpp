#include "../thread.h"
#include "../../inc/include.h"

using namespace USAF;

class TestThread : public Thread
{
public:
    bool process()
    {
        while(isRunning())
        {
            int tm = time(NULL);
            cout << tm << endl;

            usleep(500000);
        }
    }

};

int main()
{
    TestThread t;
   
    t.start();
    int a = 0;
    while(cin >> a)
    {
        if (a == 2)
        t.stop();
    }

    return 0;
}