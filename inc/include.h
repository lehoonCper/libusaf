#ifndef _INC_INCLUDE_H
#define _INC_INCLUDE_H
#include <stdio.h>
#ifdef __LINUX
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#endif
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include <mutex>
#include <iostream>
#include <fcntl.h>

//STL
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>

#include "usaf_base.h"


using namespace std;



#endif
