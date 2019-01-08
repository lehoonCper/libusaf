#pragma once

#include "../inc/include.h"
#include <memory>
namespace USAF
ZONE_START

class SessionInfo
{
public:
    SessionInfo()
    {
        
    }
    ~SessionInfo()
    {
        m_nFd = 0;
        m_nPort = 0;
        m_nConnTime = 0;
    }

#ifdef __LINUX//windows下测试用，之后删除
    bool setSession(int nFd)
    {
        sockaddr_in addr;
		socklen_t addrLen = sizeof(addr);

		getpeername(nFd, (sockaddr*)&addr, &addrLen);
		m_strAddr = string(inet_ntoa(addr.sin_addr));
		m_nPort = ntohs(addr.sin_port);
        m_nConnTime = time(NULL);
        m_nFd = nFd;
    }
#endif

    int getFd() const
    {
        return m_nFd;
    }

    int getPort() const
    {
        return m_nPort;
    }

    string& getAddr()
    {
        return m_strAddr;
    }

    int getConnTime() const
    {
        return m_nConnTime;
    }

private:
    int         m_nFd;
    int         m_nPort;
    string      m_strAddr;
    int         m_nConnTime;
};

typedef std::shared_ptr<SessionInfo> spSessionInfo;
ZONE_END