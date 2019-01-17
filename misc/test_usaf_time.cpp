#include <iostream>
#include <unistd.h>
#include "usaf_time.h"
using namespace std;
using namespace USAF;

int main()
{
    Timer time;
    cout << time.getTime() << endl;
    cout << time.getTimeMs() << endl;
    cout << time.getCostTime() << endl;
    cout << time.getCostTimeMs() << endl;

    time.resetTime();
    usleep(50000);

    cout << time.getTime() << endl;
    cout << time.getTimeMs() << endl;
    cout << time.getCostTime() << endl;
    cout << time.getCostTimeMs() << endl;

    return 0;
}