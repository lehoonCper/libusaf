#include "task.h"
#include <unistd.h>
USAF_START
Task::Task(taskList_t * pList)
{
    m_bIsOwnTaskList = false;
    if(NULL == pList)
    {
        m_pTaskList = new taskList_t;
        m_bIsOwnTaskList = true;
    }
    else
    {
        m_pTaskList = pList;
    }
}

Task::~Task()
{
    stop();
    if(true == m_bIsOwnTaskList)
    {
        delete m_pTaskList;
    }
}

bool Task::addTask(const task_t & task)
{
    m_pTaskList->push(task);
}

bool Task::process()
{
    task_t task;
    while(isRunning())
    {
        if(!m_pTaskList->pop(task))
        {
            usleep(50);
            continue;
        }
        printf("task list size:%d\n", m_pTaskList->size());
        task();
    }
    m_pTaskList->clear();
}
USAF_END