#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include <QObject>
#include <QThread>
#include <QQueue>
#include <QFuture>
#include <QWaitCondition>

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

private slots:
    void on_finished();

private:
    int m_priority;
    QFuture<void> m_future;
    QMutex m_mutex;
    QWaitCondition m_waitCondition;
    bool m_finished;
};

class TaskScheduler : public QObject
{
    Q_OBJECT
    DECLARE_SINGLETON(TaskScheduler)

public:
    TaskScheduler();
    ~TaskScheduler();

    void schedule(Task* task);

private:
    QQueue<Task*> m_queue;
    QMutex m_mutex;

private slots:
    void executeQueue();
};

}
#endif // TASKSCHEDULER_H
