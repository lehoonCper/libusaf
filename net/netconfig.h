#pragma once
#include "../inc/include.h"
#include "netdef.h"

namespace USAF
ZONE_START

class NetConfig
{
public:
    int			m_nDomain;		
	int			m_nType;
	int			m_nProtocol;

	int			m_nPort;
	string		m_strAddr;
    string      m_strModule;
	int			m_nTimeOut;


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

    NetConfigServer(int nPort, const string& strAddr)
    {
        m_nPort = nPort;
        m_strAddr = strAddr;
        m_strModule = "USAF-Service";
    }

};

ZONE_END