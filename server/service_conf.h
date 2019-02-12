#ifndef _INC_NETCONFIG_H
#define _INC_NETCONFIG_H

#include <string>

#include <inc/usaf_base.h>
#include "netdef.h"
USAF_START

class NetConfig
{
public:
    int			    m_nDomain;		
	int			    m_nType;
	int			    m_nProtocol;
    
	int			    m_nPort;
	std::string		m_strAddr;
    std::string     m_strModule;
	int			    m_nTimeOut;

    NetConfig()
    {
        init();
    }

    void init()
    {
        m_nDomain = AF_INET;
		m_nType = SOCK_STREAM;
		m_nProtocol = 0;
		m_nPort = -1;
		m_strAddr = USAF_LOCALHOST;
		m_nTimeOut = USAF_DEFAULT_TIMEOUT;
    }
};

class NetConfigServer : public NetConfig
{
public:
    int         m_nReadProcesserCnt;
    int         m_nWriteProcesserCnt;
    NetConfigServer(int nPort, const std::string& strAddr)
    {
        m_nPort = nPort;
        m_strAddr = strAddr;
        m_strModule = "USAF-Service";
        m_nReadProcesserCnt = 4;
        m_nWriteProcesserCnt = 4;
    }
};

USAF_END
#endif