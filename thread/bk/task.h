#ifndef _INC_TASK_H_
#define _INC_TASK_H_
#include <functional>
#include "../inc/usaf_base.h"
#include "../container/queue.h"
#include "thread.h"
USAF_START

typedef std::function<void(void)>   task_t;
typedef Queue<task_t>   taskList_t;

class Task : public Thread
{
public:
    Task(taskList_t* pList);
    virtual ~Task();

    bool process();
    bool addTask(const task_t& task);

private:
    taskList_t*             m_pTaskList;
    bool                    m_bIsOwnTaskList;
    task_t                  m_task;
};
USAF_END
#endif