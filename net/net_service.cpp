#include "net_service.h"
USAF_START

TcpMessageQueueMgr* TcpMessageQueueMgr::m_pInstance = NULL;
NetService::NetService()
{
    m_pConf = new NetConfigServer(8848, "localhost");
    m_accepter = NULL;
    m_pFdManager = NULL;
    m_pTcpReader = NULL;
    m_pTcpWriter = NULL;
    m_pMessageQueueMgr = NULL;
}

NetService::NetService(const NetConfigServer& conf)
{
    m_pConf = new NetConfigServer(conf.m_nPort, conf.m_strAddr);
    m_accepter = NULL;
    m_pFdManager = NULL;
    m_pTcpReader = NULL;
    m_pTcpWriter = NULL;
    m_pMessageQueueMgr = NULL;
    
}

NetService::~NetService()
{
    stop();
    if(NULL != m_accepter)
    {
       delete m_accepter;
        m_accepter = NULL;
    }
    if(NULL != m_pTcpReader)
    {
       delete m_pTcpReader;
        m_pTcpReader = NULL;
    }
    if(NULL != m_pTcpWriter)
    {
       delete m_pTcpWriter;
        m_pTcpWriter = NULL;
    }
    if(NULL != m_pFdManager)
    {
        delete m_pFdManager;
        m_pFdManager = NULL;
    }
}

bool NetService::init()
{
    if(m_flagInit)
    {
        std::cout << "[service] already inited" << std::endl;
        return true;
    }

    std::cout << "[service] Start init service" << std::endl;
//net init
    m_addr.sin_family = m_pConf->m_nDomain;
	m_addr.sin_port = htons(m_pConf->m_nPort);
	m_addr.sin_addr.s_addr = INADDR_ANY;
    m_listenFd = socket(m_pConf->m_nDomain, m_pConf->m_nType, m_pConf->m_nProtocol);
	if (m_listenFd <= 0)
	{
		std::cout << "[service] Socket Create Error: FD=" << m_listenFd << std::endl;
		return false;
	}
    std::cout << "[service] socket create ok" << std::endl;

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
        std::cout << "[service] Bind Error: BindRet=" << nBind << std::endl;
        return false;
    }
    std::cout << "[service] Bind Succeed" << std::endl;
    std::cout << "[service] Service init succeed" << std::endl;

    return true;
}

bool NetService::start()
{
    std::cout << "[service] Start NetWork" << std::endl;
    if (!init())
    {
        return false;
    }

    int nRet = listen(m_listenFd, USAF_NET_DEFAULT_LISTEN_SIZE);
	if (nRet == -1)
	{
		std::cout << "[service] Listened failed: Port=" << m_listenFd << std::endl;
        return false;
	}

    std::cout << "[service] Listen succeed: port=" << m_listenFd << std::endl;

    if(!m_pFdManager)
    {
        m_pFdManager = new FDManager();
        if(!m_pFdManager)
        {
            return false;
        }
    }

    if(!m_pMessageQueueMgr)
    {
        m_pMessageQueueMgr = TcpMessageQueueMgr::getInstance();
        if(false == m_pMessageQueueMgr->setProcesserCnt(FDManager::EpollEventType::read_event, m_pConf->m_nReadProcesserCnt))
        {
            std::cout << "[service] ReadMessageQueue Create failed" << std::endl;
            return false;
        }
        if(false == m_pMessageQueueMgr->setProcesserCnt(FDManager::EpollEventType::write_event, m_pConf->m_nWriteProcesserCnt))
        {
            std::cout << "[service] WriteMessageQueue Create failed" << std::endl;
            return false;
        }
    }
//start tcpreader thread
    if(NULL == m_pTcpReader)
    {
        m_pTcpReader = new TcpRecver(m_pFdManager);
        if(false == m_pTcpReader->start())
        {
            std::cout << "[service] TcpRecver thread Start failed" << std::endl;
            return false;
        }
    }
//start tcpwriter thread
    if(NULL == m_pTcpWriter)
    {
        m_pTcpWriter = new TcpWriter();
        if(false == m_pTcpWriter->start())
        {
            std::cout << "[service] TcpWriter thread Start failed" << std::endl;
            return false;
        }
    }
//start accepter thread
    m_accepter = new Accepter(m_listenFd, m_pFdManager);
    if(false == m_accepter->start())
    {
        std::cout << "[service] Accepter thread Start failed" << std::endl;
        return false;
    }

    std::cout << "[service] Network Start succeed" << std::endl;
    return true;
}

bool NetService::stop()
{
    std::cout << "[service] Stop Network" << std::endl;
    if(!m_accepter || !m_pTcpReader || !m_pTcpWriter)
    {
        return false;
    }
    m_accepter->stop();
    m_pTcpReader->stop();
    m_pTcpWriter->stop();
    std::cout << "[service] Network Stop succeed" << std::endl;
    return true;
}

void NetService::transPort(TCPMessage* pMsg)
{
    if(!pMsg)
    {
        return;
    }

    TcpMessageQueue* pWriteMessageQueue= m_pMessageQueueMgr->getWriteMessageQueue();
    if(pWriteMessageQueue)
    {
        pWriteMessageQueue->put(1, pMsg);
        //m_pFdManager->registeEpollEvent(pMsg->getSessionInfo()->getFd(), FDManager::EpollEventType::write_event);
    }
}





USAF_END