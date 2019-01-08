#include "../queue.h"

using namespace USAF;

int main()
{
    Queue<int> que;
    que.push(1);
    que.push(2);
    que.push(3);
    que.push(4);
    que.push(5);

    int out = -1;
    while(que.pop(out))
    {
        cout << out <<endl;
    }

}