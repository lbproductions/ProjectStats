#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include <QObject>
#include <QRunnable>
#include <QThread>
#include <QQueue>

#include <singleton.h>

class QThreadPool;

namespace Database
{

class Task : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Task(int priority = QThread::InheritPriority);

    void run();

    virtual void execute() = 0;

    int priority();

    void increasePriority();

    void decreasePriority();

signals:
    void finished();

private:
    int m_priority;
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
