#pragma once

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


using namespace std;
 

static string GL_GetModulePath()
{
	char pCurPath[200] = "";
	getcwd(pCurPath, 200);
	int nLen = strlen(pCurPath);
	return string(pCurPath, nLen);
}

#define ZONE_START {
#define ZONE_END	}


#define USAFSPACE namespace USAF

