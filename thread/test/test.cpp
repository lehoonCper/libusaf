#include "../thread.h"
#include <iostream>
#include <unistd.h>
using namespace std;
using namespace USAF;

class TestThread : public Thread
{
public:
    bool process()
    {
	cout << "TestThread started" << endl;
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
   
    if(t.start())
    {
            cout << "thread started ok" << endl;
    }
    else
    {
        cout << "thread started failed" << endl;
        return -1;
    }
/*
    while(cin >> a)
    {
        if (a == 2)
        {
            t.stop();
            cout << "stop?" << endl;
        }
    }
    */
    sleep(3);
    cout << "stop?" << endl;
    t.stop();
    
    return 0;
}
