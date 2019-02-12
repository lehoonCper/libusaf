#include <server/service.h>
#include <server/service_conf.h>
#include <iostream>
#include <unistd.h>
using namespace std;
using namespace USAF;


int main()
{
    NetConfigServer conf(8848, "localhost");
    NetService* pService = new NetService(conf);
    pService->start();

    while(true)
    {
        sleep(1);   
    }

    return 0;
}