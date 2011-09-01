#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include <QObject>
#include <QThread>
#include <QQueue>
#include <QFuture>
#include <QWaitCondition>
#include <QTimer>

#include <Misc/singleton.h>

class QThreadPool;

namespace Database
{

//! Ein Task ist ein einfaches Objekt, dass vom TaskScheduler ausgeführt werden
//! kann.
/*!
    Um einen Task auszuführen, muss eine Kindklasse davon erben und execute()
    imeplementieren.

    Anschließend kann er mit TaskScheduler::schedule() im Hintergrund ausgeführt
    werden.
  */
class Task : public QObject
{
    Q_OBJECT
public:
    /*!
        Erstellt einen neuen Task mit der Priorität \a priority.

        Die Priorität sagt dabei nicht wirklich aus, welche Priorität der Thread
        tatsächlich erhält, sondern nur, in welcher Reihenfolge die Tasks
        gestartet werden.
      */
    explicit Task(QThread::Priority priority = QThread::LowPriority, QObject* parent = 0);

    /*!
        Wird ausgeführt sobald dieser Task an der Reihe ist.
      */
    virtual void execute() = 0;

    /*!
        Gibt die aktuelle Priorität des Tasks zurück.

        \see increasePriority()
        \see decreasePriority()
      */
    QThread::Priority priority();

    /*!
        Erhöht die Priorität des Tasks um \c 1.

        Die Priorität kann nicht größer als QThread::TimeCriticalPriority
        werden.
      */
    void increasePriority();

    /*!
        Erniedrigt die Priorität des Tasks um \c 1.

        Die Priorität kann nicht kleiner als QThread::IdlePriority werden.
      */
    void decreasePriority();

    /*!
        Gibt die QFuture dieses Tasks zurück, falls er bereits gestartet wurde,
        oder eine leere QFuture, falls er noch wartet.
      */
    QFuture<void> future() const;

    /*!
        Wartet bis der Task beendet wurde. Das gilt natürlich auch, falls er
        noch gar nicht gestartet wurde.

        Während des Wartens wird die Priorität des Tasks erhöht, sodass gilt:
        Je mehr andere Threads auf den Task warten, desto höher ist seine
        Priorität.

        Außerdem werden mit Hilfe von QThreadPool::releaseThread() der Thread
        freigegeben, sodass die Resourcen genutzt werden können.

        Tut nichts, falls der Task schon beendet wurde.
      */
    void waitForFinished();

signals:
    /*!
        Wird gesendet, sobald execute() verlassen wurde und alle wartenden
        Threads geweckt wurden.
      */
    void finished();

    /*!
        Wird gesendet, sobald ein anderer Thread auf diesen Task wartet.
      */
    void waiting();

private:
    //damit setFuture(), run(), lock() und unlock() zur Verfügung stehen:
    friend class ExecuteQueueHelper;

    /*!
        Setzt die QFuture des Tasks auf \a future
      */
    void setFuture(QFuture<void> future);

    /*!
        Führt den Task aus.

        Sperrt zunächst alle weiteren Zugriffe mit lock() und startet dann
        execute().

        Anschließend werden alle dann wartenden Tasks geweckt und finished()
        gesendet.
      */
    void run();

    /*!
        Sperrt den Mutex des Tasks.
      */
    void lock();

    /*!
        Entsperrt den Mutex des Tasks.
      */
    void unlock();

    QThread::Priority m_priority; //!< Die Priorität des Tasks
    QFuture<void> m_future; //!< Die QFuture des Tasks, sobald er gestartet wurde
    QMutex m_mutex; //!< Dieser Mutex sperrt alle Methoden des Tasks.
    QWaitCondition m_waitCondition; //!< Diese QWaitCondition wartet bis der Tasks beendet wurde
    QMutex m_waitingMutex; //!< Unterstützt m_waitCondition
    bool m_finished; //!< \c true, sobald der Task beendet wurde
};

class ExecuteQueueHelper;

//! Der TaskScheduler ist für das Ausführen von Tasks verantwortlich.
/*!
    Ein Task kann an die Methode schedule() übergeben werden und reiht sich dann
    in eine Warteschlange ein, die Regelmäßig nach den Prioritäten der Tasks
    sortiert wird.

    Werden Resourcen (sprich Threads) frei, startet der TaskScheduler weitere
    Tasks aus seiner Warteschlange, solange bis keine Threads mehr zur Verfügung
    stehen, oder keine Tasks mehr vorhanden sind.

    Der TaskScheduler ist dabei ein eigener Thread, sodass er nicht warten muss,
    falls die GUI gerade auf irgendetwas wartet.

    Außerdem ist TaskScheduler ein Singleton, sodass von überall aus auf ihn
    zugegriffen werden kann.
  */
class TaskScheduler : public QThread
{
    Q_OBJECT
    DECLARE_SINGLETON(TaskScheduler)

public:
    TaskScheduler();
    ~TaskScheduler();

    void schedule(Task* task);

    void run();

public slots:
    void shutdown();

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

    int m_startedTasks;
    static const int m_sortAfterCount = 10;
};

}
#endif // TASKSCHEDULER_H
