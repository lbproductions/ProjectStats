#include "taskscheduler.h"

#if QT_VERSION >= 0x050000
#include <QtConcurrent/QtConcurrent>
#else
#include <QtConcurrentRun>
#endif

#include <Misc/handler.h>

using namespace Database;

bool priorityIsHigher(Task* t1, Task* t2)
{
    return t1->priority() > t2->priority();
}

ExecuteQueueHelper::ExecuteQueueHelper(TaskScheduler *parent) :
    QObject(),
    m_taskScheduler(parent),
    m_startedTasks(0)
{
}

void ExecuteQueueHelper::executeQueue()
{
    m_taskScheduler->m_mutex.lock();
    qSort(m_taskScheduler->m_queue.begin(),m_taskScheduler->m_queue.end(),priorityIsHigher);

    while(!m_taskScheduler->m_queue.isEmpty()
          && QThreadPool::globalInstance()->activeThreadCount() < QThreadPool::globalInstance()->maxThreadCount())
    {
        Task* task = m_taskScheduler->m_queue.dequeue();
        task->lock();
        QFuture<void> future = QtConcurrent::run(task, &Task::run);
        task->setFuture(future);
        task->unlock();
    }
    m_taskScheduler->m_mutex.unlock();
}

Task::Task(QThread::Priority priority, QObject* parent) :
    QObject(parent),
    m_priority(priority),
    m_mutex(QMutex::NonRecursive),
    m_finished(false)
{
    if(m_priority == QThread::InheritPriority)
    {
        m_priority = QThread::currentThread()->priority();
    }
    else
    {
        //QThread::currentThread()->setPriority(m_priority);
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

const QThread::Priority& Task::priority()
{
    return m_priority;
}

void Task::increasePriority()
{
    lock();
    m_priority = (QThread::Priority) ((int)m_priority + 1);
    unlock();
}

void Task::decreasePriority()
{
    lock();
    m_priority = (QThread::Priority) ((int)m_priority - 1);
    unlock();
}

void Task::run()
{
    execute();
    lock();
    m_waitingMutex.lock();
    m_waitCondition.wakeAll();
    m_waitingMutex.unlock();
    m_finished = true;
    unlock();
    emit finished();
}

void Task::execute()
{
}

void Task::waitForFinished()
{
    QThreadPool::globalInstance()->releaseThread();
    emit waiting();
    lock();
    m_priority = (QThread::Priority) ((int)m_priority + 1);
    while(!m_finished)
    {
        m_waitingMutex.lock();
        unlock();
        m_waitCondition.wait(&m_waitingMutex);
        lock();
        m_waitingMutex.unlock();
    }
    m_priority = (QThread::Priority) ((int)m_priority - 1);

    unlock();
    QThreadPool::globalInstance()->reserveThread();
    decreasePriority();
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
    QThreadPool::globalInstance()->releaseThread();
    exec();
}

void TaskScheduler::shutdown()
{
    //QThreadPool::globalInstance()->waitForDone();
}

TaskScheduler::~TaskScheduler()
{
    m_executeQueueHelper->deleteLater();
}

void TaskScheduler::schedule(Task* task)
{
    QThreadPool::globalInstance()->reserveThread();
    m_mutex.lock();
    m_queue.enqueue(task);
    connect(task,SIGNAL(finished()),m_executeQueueHelper,SLOT(executeQueue()));
    connect(task,SIGNAL(waiting()),m_executeQueueHelper,SLOT(executeQueue()));
    m_mutex.unlock();
    emit newTaskScheduled();
    QThreadPool::globalInstance()->releaseThread();
}
