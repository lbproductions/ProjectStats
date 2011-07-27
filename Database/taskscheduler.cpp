#include "taskscheduler.h"

#include <QThreadPool>

using namespace Database;


Task::Task(int priority) :
    QRunnable(),
    m_priority(priority)
{
    if(m_priority == QThread::InheritPriority)
    {
        m_priority = QThread::currentThread()->priority();
    }
}

int Task::priority()
{
    return m_priority;
}

void Task::increasePriority()
{
    ++m_priority;
}

void Task::decreasePriority()
{
    --m_priority;
}

void Task::run()
{
    execute();
    emit finished();
}

IMPLEMENT_SINGLETON(TaskScheduler)

TaskScheduler::TaskScheduler() :
    QObject(),
    m_queue(QQueue<Task*>()),
    m_mutex(QMutex::Recursive)
{
}

TaskScheduler::~TaskScheduler()
{
    QThreadPool::globalInstance()->waitForDone();
}

void TaskScheduler::schedule(Task* task)
{
    m_mutex.lock();
    m_queue.enqueue(task);
    connect(task,SIGNAL(finished()),this,SLOT(executeQueue()));
    executeQueue();
    m_mutex.unlock();
}

void TaskScheduler::executeQueue()
{
    static QThreadPool* pool = QThreadPool::globalInstance();
    m_mutex.lock();
    while(!m_queue.isEmpty() && pool->activeThreadCount() < pool->maxThreadCount())
    {
        Task* task = m_queue.dequeue();
        pool->start(task, task->priority());
    }
    m_mutex.unlock();
}
