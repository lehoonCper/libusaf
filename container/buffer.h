#ifndef _INC_BUFFER_H_
#define _INC_BUFFER_H_
#include "../inc/usaf_base.h"
#include "../misc/obj_pool.h"
#include <string.h>
USAF_START

class Buffer
{
public:
    Buffer(size_t nSize)
    {
        m_pData = new char[nSize];
        memset(m_pData, 0, nSize);
        m_nSize = nSize;
    }

    Buffer(const char* pData, size_t nSize)
    {
        m_pData = new char[nSize];
        memcpy(m_pData, pData, nSize);
        m_nSize = nSize;
    }

    Buffer(const Buffer& ref)
    {
        m_nSize = ref.m_nSize;
        m_pData = new char[m_nSize];
        memcpy(m_pData, ref.m_pData, m_nSize);
    }

    virtual ~Buffer()
    {
        if(NULL != m_pData)
        {
            delete[] m_pData;
        }
    }

    size_t reBuffer(const char* pData, int nSize)
    {
        if(nSize > m_nSize)
        {
            delete m_pData;
            m_pData = new char[nSize];
        }
        memcpy(m_pData, pData, nSize);
        m_nSize = nSize;
    }

    inline char* getData() const
    {
        return m_pData;
    }

    inline size_t size() const
    {
        return m_nSize;
    }

private:
    char*   m_pData;
    size_t  m_nSize;
};

static Buffer* alloc_buffer_func(void)
{
    return new Buffer(10000);
}

class BufferPool
{
public:
    static BufferPool* getInstance()
    {
        if(NULL == m_pInstance)
        {
            m_pInstance = new BufferPool();
        }
        return m_pInstance;
    }

    Buffer* invoke()
    {
        return NULL == m_pPool ? NULL : m_pPool->AskObj();
    }

    void release(Buffer* pBuffer)
    {
        if(m_pPool && NULL != pBuffer)
        {
            m_pPool->ReturnObj(pBuffer);
        }
    }
    
    static BufferPool* m_pInstance;

private:
    ObjPool<Buffer>* m_pPool;

protected:
    BufferPool()
    {
        m_pPool = new ObjPool<Buffer>(10000, 1000, alloc_buffer_func);
    }

    virtual ~BufferPool()
    {
        delete m_pPool;
    }
};
USAF_END
#endif