#include "task_pool.h"
USAF_START

TaskPool::TaskPool(int nProcesserSize)
{
    m_pTaskList = new taskList_t;
    m_nProcesserCnt = nProcesserSize;
    for(int i = 0; i < m_nProcesserCnt; ++i)
    {
        m_vtTaskProcesser.push_back(new Task(m_pTaskList));
    }
}

TaskPool::~TaskPool()
{
    stop();
    if(NULL != m_pTaskList)
    {
        delete m_pTaskList;
        m_pTaskList = NULL;
    }
    for(Task* pTask : m_vtTaskProcesser)
    {
        delete pTask;
        pTask = NULL;
    }
}

bool TaskPool::start()
{
    for(auto iter : m_vtTaskProcesser)
    {
        iter->start();
    }
}

bool TaskPool::stop()
{
    for(auto iter : m_vtTaskProcesser)
    {
        iter->stop();
    }
}

bool TaskPool::addTask(const task_t & task)
{
    m_pTaskList->push(task);
}
USAF_END