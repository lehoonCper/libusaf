#include "../net_service.h"
#include "../../inc/usaf_base.h"
using namespace USAF;
extern int errno;
int main()
{
    NetConfigServer conf(8848, "localhost");
    NetService serv(conf);

    serv.start();

    while(true)
    {
    	sleep(1);
    	cout << "service running..." << endl;
    }

    return 0;
}
