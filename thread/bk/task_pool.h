#ifndef _INC_TASK_POOL_H_
#define _INC_TASK_POOL_H_
#include "../container/queue.h"
#include <functional>
#include "../inc/usaf_base.h"
#include "task.h"
USAF_START

class TaskPool
{
public:
    TaskPool(int nProcesserCnt = 4);
    virtual ~TaskPool();

    bool start();
    bool stop();
    bool setProcesserCnt(int nCnt);

    bool addTask(const task_t& task);
private:
    taskList_t*             m_pTaskList;               
    std::vector<Task*>      m_vtTaskProcesser;        
    int                     m_nProcesserCnt;  
};

USAF_END
#endif