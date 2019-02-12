#include "service.h"
USAF_START

NetService::NetService(const NetConfigServer& conf)
{
    m_pConf = new NetConfigServer(conf.m_nPort, conf.m_strAddr);
    m_pFdManager = NULL;
}

NetService::~NetService()
{
    stop();
    if(NULL != m_pFdManager)
    {
        delete m_pFdManager;
        m_pFdManager = NULL;
    }
}

bool NetService::startNet()
{
    if(m_flagInit)
    {
        std::cout << "[service] already inited" << std::endl;
        return true;
    }

    std::cout << "[service] Start init service" << std::endl;
//net init
    sockaddr_in stSockAddr;
    stSockAddr.sin_family = m_pConf->m_nDomain;
	stSockAddr.sin_port = htons(m_pConf->m_nPort);
	stSockAddr.sin_addr.s_addr = INADDR_ANY;
    m_listenFd = socket(m_pConf->m_nDomain, m_pConf->m_nType, m_pConf->m_nProtocol);
	if (m_listenFd <= 0)
	{
		std::cout << "[service] Socket Create Error: FD=" << m_listenFd << std::endl;
		return false;
	}
    std::cout << "[service] socket create ok" << std::endl;

//bind
    int nBind = bind(m_listenFd, (struct sockaddr*)&stSockAddr, sizeof(stSockAddr));	
    if (nBind == -1)
    {
        std::cout << "[service] Bind Error: BindRet=" << nBind << std::endl;
        return false;
    }
    std::cout << "[service] Bind Succeed" << std::endl;

//listen
    int nRet = listen(m_listenFd, 10);
	if (nRet == -1)
	{
		std::cout << "[service] Listened failed: Port=" << m_listenFd << std::endl;
        return false;
	}
    std::cout << "[service] Listen succeed: port=" << m_listenFd << std::endl;

    std::cout << "[service] Service init succeed" << std::endl;

    return true;
}

bool NetService::start()
{
    std::cout << "[service] Start NetWork" << std::endl;
    if (!startNet())
    {
        return false;
    }

    if(!m_pFdManager)
    {
        m_pFdManager = new FDManager(m_listenFd);
        if(!m_pFdManager)
        {
            return false;
        }
    }

    std::cout << "[service] Network Start succeed" << std::endl;
    return true;
}

bool NetService::stop()
{
    std::cout << "[service] Stop Network" << std::endl;
    std::cout << "[service] Network Stop succeed" << std::endl;
    return true;
}






USAF_END