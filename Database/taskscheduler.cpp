#include "taskscheduler.h"

#include <QtConcurrentRun>

using namespace Database;


Task::Task(int priority, QObject* parent) :
    QObject(parent),
    m_priority(priority),
    m_mutex(QMutex::Recursive),
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
    lock();
    m_future = future;
    unlock();
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
    connect(this,SIGNAL(finished()),this,SLOT(on_finished()));
    lock();
    execute();
    unlock();
    emit finished();
}

void Task::waitForFinished()
{
    m_future.waitForFinished();
}

void Task::on_finished()
{
    lock();
    m_finished = true;
    unlock();
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

bool priorityIsHigher(Task* t1, Task* t2)
{
    return t1->priority() < t2->priority();
}

void TaskScheduler::executeQueue()
{
    m_mutex.lock();
    qSort(m_queue.begin(),m_queue.end(),priorityIsHigher);
    while(!m_queue.isEmpty() && QThreadPool::globalInstance()->activeThreadCount() < QThreadPool::globalInstance()->maxThreadCount())
    {
        Task* task = m_queue.dequeue();
        task->lock();
        QFuture<void> future = QtConcurrent::run(task, &Task::run);
        task->setFuture(future);
        task->unlock();
    }
    m_mutex.unlock();
}
