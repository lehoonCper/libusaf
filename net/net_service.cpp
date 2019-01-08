#include "net_service.h"

namespace USAF
ZONE_START

NetService::NetService()
{
    m_pConf = new NetConfigServer(8848, "localhost");
    m_accepter = NULL;
}

NetService::NetService(const NetConfigServer& conf)
{
    m_pConf = new NetConfigServer(conf.m_nPort, conf.m_strAddr);
    
}

bool NetService::init()
{
    if(m_flagInit)
    {
        cout << "already inited" << endl;
        return true;
    }
//member init




//net init
    m_addr.sin_family = m_pConf->m_nDomain;
	m_addr.sin_port = htons(m_pConf->m_nPort);
	m_addr.sin_addr.s_addr = INADDR_ANY;
    m_listenFd = socket(m_pConf->m_nDomain, m_pConf->m_nType, m_pConf->m_nProtocol);
	if (m_listenFd <= 0)
	{
		cout << "Socket Create Error: FD=" << m_listenFd << endl;
		return false;
	}
    cout << "socket create ok" << endl;

//set noblock
/*
    int nFlag = fcntl(m_listenFd, F_GETFL, 0);
    nFlag |= O_NONBLOCK;
    fcntl(m_listenFd, F_SETFL, nFlag);
    */

//bind
    int nBind = bind(m_listenFd, (struct sockaddr*)&m_addr, sizeof(m_addr));	
    if (nBind == -1)
    {
        cout << "Bind Error: BindRet=" << nBind << endl;
        return false;
    }
    cout << "Bind Succeed" << endl;

    return true;
}

bool NetService::start()
{
    if (!init())
    {
        return false;
    }

    int nRet = listen(m_listenFd, USAF_NET_DEFAULT_LISTEN_SIZE);
	if (nRet == -1)
	{
		cout << "Listened failed: Port=" << m_listenFd << endl;
        return false;
	}

    cout << "Listen succeed: port=" << m_listenFd << endl;

//start accept thread
    m_accepter = new Accepter(m_listenFd);
    m_accepter->start();

    cout << "Accept start" << endl;
    return true;
}

bool NetService::stop()
{
    return true;
}



ZONE_END