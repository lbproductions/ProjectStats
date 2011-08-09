#include "taskscheduler.h"

#include <QtConcurrentRun>
#include <handler.h>

using namespace Database;


Task::Task(int priority, QObject* parent) :
    QObject(parent),
    m_priority(priority),
    m_mutex(QMutex::NonRecursive),
    m_finished(false)
{
    if(m_priority == QThread::InheritPriority)
    {
        m_priority = QThread::currentThread()->priority();
    }
}

void Task::lock()
{
    m_mutex.lock();
}

void Task::unlock()
{
    m_mutex.unlock();
}

void Task::setFuture(QFuture<void> future)
{
    m_future = future;
}

QFuture<void> Task::future() const
{
    return m_future;
}

int Task::priority()
{
    return m_priority;
}

void Task::increasePriority()
{
    lock();
    ++m_priority;
    unlock();
}

void Task::decreasePriority()
{
    lock();
    --m_priority;
    unlock();
}

void Task::run()
{
    lock();
    execute();
    m_waitCondition.wakeAll();
    m_finished = true;
    unlock();
    emit finished();
}

void Task::waitForFinished()
{
    ++m_priority;
    QThreadPool::globalInstance()->releaseThread();
    if(!m_finished)
    {
        m_waitingMutex.lock();
        m_waitCondition.wait(&m_waitingMutex);
        m_waitingMutex.unlock();
    }
    QThreadPool::globalInstance()->reserveThread();
}

IMPLEMENT_SINGLETON(TaskScheduler)

TaskScheduler::TaskScheduler() :
    QThread(),
    m_queue(QQueue<Task*>()),
    m_mutex(QMutex::Recursive)
{
}

void TaskScheduler::run()
{
    m_executeQueueHelper = new ExecuteQueueHelper(this);
    connect(this,SIGNAL(newTaskScheduled()),m_executeQueueHelper,SLOT(executeQueue()));
    exec();
}

TaskScheduler::~TaskScheduler()
{
    m_executeQueueHelper->deleteLater();
    m_timer->deleteLater();
    QThreadPool::globalInstance()->waitForDone();
}

void TaskScheduler::schedule(Task* task)
{
    m_mutex.lock();
    m_queue.enqueue(task);
    connect(task,SIGNAL(finished()),m_executeQueueHelper,SLOT(executeQueue()));
    m_mutex.unlock();
    emit newTaskScheduled();
}

bool priorityIsHigher(Task* t1, Task* t2)
{
    return t1->priority() < t2->priority();
}

ExecuteQueueHelper::ExecuteQueueHelper(TaskScheduler *parent) :
    QObject(),
    m_taskScheduler(parent)
{
}

void ExecuteQueueHelper::executeQueue()
{
    m_taskScheduler->m_mutex.lock();
    qSort(m_taskScheduler->m_queue.begin(),m_taskScheduler->m_queue.end(),priorityIsHigher);
    while(!m_taskScheduler->m_queue.isEmpty() && QThreadPool::globalInstance()->activeThreadCount() < QThreadPool::globalInstance()->maxThreadCount())
    {
        Task* task = m_taskScheduler->m_queue.dequeue();
        task->lock();
        QFuture<void> future = QtConcurrent::run(task, &Task::run);
        task->setFuture(future);
        task->unlock();
    }
    m_taskScheduler->m_mutex.unlock();
}
