#ifndef _INC_OBJ_POOL_H_
#define _INC_OBJ_POOL_H_
#include "../inc/usaf_base.h"
#include <mutex>
#include <functional>
USAF_START

template<class obj_t>
class ObjPool
{
public:
typedef obj_t* obj_array_t;
typedef std::function<obj_t* (void)> alloc_t;
typedef std::function<void(obj_t *)> release_t;

    ObjPool(int nPoolSize, int nAllocSize, 
    const alloc_t& allocFunc = defaultAllocFunc, const release_t& releaseFunc = defaultReleaseFunc)
    {//make sure poolsize > allocsize
        if(nPoolSize < nAllocSize)
        {
            return;
        }
        m_nPoolSize = nPoolSize;
        m_nAllocSize = nAllocSize;
        m_funcAlloc = allocFunc;
        m_funcRelease = releaseFunc;
        m_nCurSize = nAllocSize - 1;

        m_pObjArray = new obj_array_t[m_nPoolSize];
        for(int i = 0; i < m_nAllocSize; ++i)
        {
            m_pObjArray[i] = m_funcAlloc();
        }
        m_pMutex = new std::mutex();
    }

    ~ObjPool()
    {
        if(m_pMutex)
        {
            delete m_pMutex;
        }
        for(int i = 0; i < m_nAllocSize; ++i)
        {
            m_funcRelease(m_pObjArray[i]);
        }
        delete[] m_pObjArray;
    }

    obj_t* AskObj()
    {
        obj_t* pObj = NULL;
        m_pMutex->lock();
        if(m_nCurSize > 0 && m_nCurSize < m_nAllocSize)
        {
            pObj = m_pObjArray[m_nCurSize];
            if(m_nCurSize >= 1)
            {
                --m_nCurSize;
            }
        }
        else
        {
            if(m_nAllocSize < m_nPoolSize)
            {
                 pObj = m_funcAlloc();
                static int allocCnt = 0;
                ++m_nAllocSize;
                printf("alloc cnt: %d, toptal: A_%d, C_%d, P_%d\n", allocCnt++, m_nAllocSize, m_nCurSize, m_nPoolSize);
            }
        }
        m_pMutex->unlock();
        return pObj;
    }

    void ReturnObj(obj_t* obj)
    {
        if(NULL == obj)
        {
            return;
        }
        m_pMutex->lock();
        if(m_nCurSize < m_nPoolSize)
        {
            m_pObjArray[m_nCurSize++] = obj;
        }
        //static int cnt = 0;
        //printf("return cnt: %d, toptal: A_%d, C_%d, P_%d\n", cnt++, m_nAllocSize, m_nCurSize, m_nPoolSize);
        m_pMutex->unlock();
    }

    static obj_t* defaultAllocFunc()
    {
        return new obj_t;
    }

    static void defaultReleaseFunc(obj_t* pObj)
    {
        delete pObj;
    }

private:
    int             m_nPoolSize;            //pool-zone-size    decided when construct
    int             m_nAllocSize;           //useable-obj-size  dynamic adjust when using
    int             m_nCurSize;              //index-of-obj      marking useable obj pos
    obj_t**         m_pObjArray;
    std::mutex*     m_pMutex; 
    alloc_t         m_funcAlloc;
    release_t       m_funcRelease;
};

USAF_END
#endif