#ifndef _INC_SESSION_H
#define _INC_SESSION_H

#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <inc/usaf_base.h>
#include <misc/usaf_time.h>
USAF_START

class NetInfo
{
public:
    NetInfo()
    {
        m_nFd = 0;
        m_nPort = 0;
        m_pTime = new Timer();
    }
    ~NetInfo()
    {
        m_nFd = 0;
        m_nPort = 0;
        if(m_pTime)
        {
            delete m_pTime;
            m_pTime = NULL;
        }
    }

    NetInfo(NetInfo* pRef)
    {
        if(pRef)
        {
            m_nFd = pRef->m_nFd;
            m_nPort = pRef->m_nPort;
            m_strAddr = pRef->m_strAddr;
            m_pTime = new Timer();
            m_pTime->copy(pRef->m_pTime);
        }
    }

    void setNetInfo(int nFd)
    {
        sockaddr_in addr;
		socklen_t addrLen = sizeof(addr);

		getpeername(nFd, (sockaddr*)&addr, &addrLen);
		m_strAddr = std::string(inet_ntoa(addr.sin_addr));
		m_nPort = ntohs(addr.sin_port);
        m_pTime->resetTime();
        m_nFd = nFd;
    }

    int getFd() const
    {
        return m_nFd;
    }

    int getPort() const
    {
        return m_nPort;
    }

    std::string& getAddr()
    {
        return m_strAddr;
    }

    Timer* getTimer() const
    {
        return m_pTime;
    }

private:
    int             m_nFd;
    int             m_nPort;
    std::string     m_strAddr;
    Timer*          m_pTime;
};

USAF_END
#endif