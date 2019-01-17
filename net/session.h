#ifndef _INC_SESSION_H
#define _INC_SESSION_H

#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../inc/usaf_base.h"
#include "../misc/usaf_time.h"
USAF_START

class SessionInfo
{
public:
    SessionInfo()
    {
        m_pConnTime = NULL;
    }
    ~SessionInfo()
    {
        m_nFd = 0;
        m_nPort = 0;
        if(m_pConnTime)
        {
            delete m_pConnTime;
            m_pConnTime = NULL;
        }
    }

    bool setSession(int nFd)
    {
        sockaddr_in addr;
		socklen_t addrLen = sizeof(addr);

		getpeername(nFd, (sockaddr*)&addr, &addrLen);
		m_strAddr = std::string(inet_ntoa(addr.sin_addr));
		m_nPort = ntohs(addr.sin_port);
        m_pConnTime = new Timer();
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

    Timer* getConnTime() const
    {
        return m_pConnTime;
    }

private:
    int             m_nFd;
    int             m_nPort;
    std::string     m_strAddr;
    Timer*          m_pConnTime;
};

typedef std::shared_ptr<SessionInfo> spSessionInfo;
USAF_END
#endif