#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include <QObject>
#include <QThread>
#include <QQueue>
#include <QFuture>
#include <QWaitCondition>
#include <QTimer>

#include <singleton.h>

class QThreadPool;

namespace Database
{

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(int priority = QThread::InheritPriority, QObject* parent = 0);

    void run();

    virtual void execute() = 0;

    int priority();

    void increasePriority();

    void decreasePriority();

    void setFuture(QFuture<void> future);

    QFuture<void> future() const;

    void waitForFinished();

    void lock();
    void unlock();

signals:
    void finished();

private:
    int m_priority;
    QFuture<void> m_future;
    QMutex m_mutex;
    QWaitCondition m_waitCondition;
    QMutex m_waitingMutex;
    bool m_finished;
};

class TaskScheduler;

class ExecuteQueueHelper : public QObject
{
    Q_OBJECT

public:
    friend class TaskScheduler;

    explicit ExecuteQueueHelper(TaskScheduler* parent = 0);

public slots:
    void executeQueue();

private:
    TaskScheduler* m_taskScheduler;
};

class TaskScheduler : public QThread
{
    Q_OBJECT
    DECLARE_SINGLETON(TaskScheduler)

public:
    TaskScheduler();
    ~TaskScheduler();

    void schedule(Task* task);

    void run();

private:
    QQueue<Task*> m_queue;
    QMutex m_mutex;
    QTimer* m_timer;

signals:
    void newTaskScheduled();

private:
    ExecuteQueueHelper* m_executeQueueHelper;

    friend class ExecuteQueueHelper;
};

}
#endif // TASKSCHEDULER_H
