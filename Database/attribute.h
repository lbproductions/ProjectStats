#ifndef DATABASE_ATTRIBUTE_H
#define DATABASE_ATTRIBUTE_H

#include <QObject>

#include <QPointer>
#include <QMutex>
#include <QVariant>
#include <QWaitCondition>
#include <QFuture>
#include <QThreadPool>
#include <QDebug>
#include <QMutexLocker>

#include <handler.h>
#include "attributevariant.h"
#include "taskscheduler.h"

/*!
  Ruft auf dem Objekt \p object die Funktion \p ptrToMember auf.<br>
  \p object muss ein Pointer auf eine Klasse sein, und \p ptrToMember ein Pointer zu einer Funktion dieser Klasse.<br>

  \code Row *row; CALL_MEMBER_FN(row, &Row::set)("name",value);
  */
#define CALL_MEMBER_FN(object,ptrToMember)  ((*object).*(ptrToMember))

class QLabel;
class QLineEdit;

namespace Database {

class Changeable : public QObject
{
    Q_OBJECT
public:
    explicit Changeable(QObject *parent = 0);

    virtual const QString toString();

signals:
    void changed();
};

class Player;

class AttributeBase;
class AttributeFutureWatcher;

class AttributeOwner : public Changeable
{
    Q_OBJECT
public:
    explicit AttributeOwner(QObject *parent = 0);

    /*!
      Gibt alle Attribute dieser Row zurück.

      \return Alle Attribute dieser Row
      */
    virtual QList<AttributeBase*> attributes() const = 0;

    /*!
      Gibt das Attribut mit dem Namen \p name oder 0 zurück, falls es dieses nicht gibt.

      \return das Attribut mit dem Namen \p name oder 0, falls es dieses nicht gibt.
      */
    virtual AttributeBase *attribute(const QString &name) const = 0;
};

//! Dieses Interface dient dazu, der template-Klasse Attribute signals und slots, sowie ein Dasein als QObject zu ermöglichen.
/*!
  In Qt ist es nicht möglich dass template-Klassen QObjects sind oder mit Hilfe des Q_OBJECT Macros über signals und slots verfügen. Aus diesem Grund haben wir diese Elternklasse, von der Attribute erben kann, die diese Funktionalitäten enthält und damit auch für seine Kindklasse bereitstellt.
  */
class AttributeBase : public Changeable
{
    Q_OBJECT
public:
    /*!
      Wird benutzt um Rows als MetaType registrieren zu können. Niemals benutzen!
      */
    AttributeBase();

    /*!
      Erstellt ein Attribut für die Row \p row.
      */
    explicit AttributeBase(const QString &name, const QString &displayName, AttributeOwner *row);

    /*!
      Gibt true zurück, falls das Attribut ein Datenbankattribut ist.<br>
      Diese standardimplementierung gibt false zurück.

      \return false
      */
    virtual bool isDatabaseAttribute() const;

    /*!
      Gibt den Namen des Attributs zurück.

      \return Der Name des Attributs.
      */
    QString name() const;

    QString displayName() const;

    int role() const;

    void setRole(int role);

    AttributeOwner *owner() const;

    /*!
      Gibt den SQL-Typen dieses Attributs zurück. (z.B. QString -> TEXT, int -> Int).

      \return der SQL-Typen dieses Attributs.
      */
    virtual QString sqlType() const = 0;

    virtual const AttributeVariant toVariant() = 0;
    virtual const QString toString() = 0;
    virtual const QVariant displayVariant() = 0;
    virtual void changeValue(QVariant value, bool updateDatabase);

    virtual AttributeFutureWatcher* startCalculationTask() = 0;

    virtual bool isCalculating() = 0;

    void emitChanged();

    void setDisplayRole(AttributeVariant::DisplayRole role);

    AttributeVariant::DisplayRole displayRole();

    void setEmitChange(bool check);

public slots:
    virtual void changeValue(const QVariant& value) = 0;
    void changeValue(int value);

protected slots:
    /*!
      Berechnet den Wert des Attributs komplett neu.
      */
    virtual void recalculateFromScratch() = 0;

    /*!
      Wird aufgerufen, falls sich Attribute ändern, von denen dieses Attribut abhängt.<br>
      Ist das Attribut noch nicht initialisiert oder keine Updatefunktion gegeben, wird das Attribut komplett neu berechnet.<br>
      Sonst wird zunächst die Updatefunktion nach einem neuen Wert gefragt.<br>
      Kann diese aus den gegebenen Änderungen der geänderten Abhängigkeit keinen neuen Wert berechnen, wird das Attribut komplett neu berechnet.
      */
    virtual void updateFromDependency() = 0;

    virtual void onChange();

    virtual void endCalculation() = 0;

signals:
    /*!
      Wird gesendet, sobald sich das Attribut geändert hat.
      */
    void changed();

    /*!
      Wird gesendet, kurz bevor ein Hintergrundtask für die Berechnung oder Update dieses Attributs gestartet wird.<br>
      Ist der Task beendet wird changed() gesendet.
      */
    void aboutToChange();

protected:

    AttributeOwner *m_owner; //!< Die Row, zu dem das Attribut gehört.

    QString m_name;
    QString m_displayName;
    int m_role;
    QList<AttributeBase*> m_dependingAttributes;

    AttributeVariant::DisplayRole m_displayRole;
    bool m_emitChange;
};

template<class AttributeType, class ValueType>
class RecalculationTask;

template<class RowType, class Owner>
class TableModel;

template<class RowType>
class Table;

//! Repräsentiert ein Attribut einer Row.
/*!
  Diese Klasse kümmert sich um sehr viele Aspekte eines Attributs.<br>
  Ein zentraler Punkt dieser Klasse ist der eingebaute Cache für den Wert des Attributs. Dieser ist zunächst uninitialisiert und wird erst mit dem ersten Zugriff befüllt.<br>
  Attribute können von einander abhängen. Ändert sich dann ein Attribut berechnen alle abhängigen Attribute ihren Wert neu.<br>
  <br>
  Die Klasse beschäftigt sich zudem viel damit, Berechnungen und Zugriffe in den Hintergrund zu verlagern. Zu diesem Zweck enthält es einen eigenen AttributeFutureWatcher, die Hintergrundberechnungen beobachtet und das Attribut entsprechend anpasst.<br>
  Der AttributeFutureWatcher kann zudem dazu verwendet werden GUI Elemente mit dem Attribut zu verknüpfen und so zukünftige Änderungen am Attribut widerspiegeln lassen.<br>
  <br>
  Die Klasse sollte außerdem so weit es mir möglich war Threadsicher sein.
  */
template<class T, class R, class C>
class Attribute : public AttributeBase
{
public:
    typedef T (C::*CalculateFunction)(); //!< Die Signatur der Calculatefunction
    typedef QFuture<T> (C::*UpdateFunction)(AttributeBase *changedDependency); //!< Die Signatur der Updatefunction
    typedef T (C::*AttributeSpecificUpdateFunction)();
    /*!
      Wird benutzt um Rows als MetaType registrieren zu können. Niemals benutzen!
      */
    Attribute();

    ~Attribute();

    /*!
      Erstellt ein Attribut für die Row \p row.
      */
    Attribute(const QString &name, const QString &displayName, AttributeOwner *owner);

    /*!
      Gibt den Wert des Attributs zurück.<br>
      Ist der Cache ungültig oder leer, wird er zuvor synchron neu berechnet.

      \return der Wert des Attributs.
      */
    virtual const T value();

    const AttributeVariant toVariant();

    const QString toString();

    const QVariant displayVariant();
    /*!
      Startet im Hintergrund eine Neuberechnung des Attributs und
      gibt den AttributeFutureWatcher dieses Attributs zurück.

      \return der AttributeFutureWatcher dieses Attributs.
      */
    AttributeFutureWatcher* startCalculationTask();

    /*!
      Gibt den AttributeFutureWatcher dieses Attributs zurück.

      \return der AttributeFutureWatcher dieses Attributs.
      */
    AttributeFutureWatcher* futureWatcher();

    /*!
      Setzt die Calculationfunction dieses Attributs auf \p calculateFuntion.<br>
      Wie das geht, kann man sich gut bei bestehenden Rows abgucken.
      */
    virtual void setCalculationFunction(C* calculator, CalculateFunction calculateFuntion);

    /*!
      Setzt die Updatefunction dieses Attributs auf \p updateFunction.<br>
      Wie das geht, kann man sich gut bei bestehenden Rows abgucken.
      */
    void setUpdateFunction(C* calculator, UpdateFunction updateFunction);

    /*!
      Fügt eine Updatefunction \p updateFunction zu diesem Attribut hinzu.<br>
      Diese wird dann aufgerufen, wenn sich das Attribut \p attribute geändert hat.<br>
      */
    void setUpdateFunction(AttributeBase* attribute, AttributeSpecificUpdateFunction updateFunction);

    /*!
      Geschrieben um den Zugriff auf Attribute zu erleichern.<br>
      Statt row->attribute.value() lässt sich nun kürzer schreiben row->attribute() um den Wert zu erhalten.

      \see value()
      \return der Wert des Attributs.
      */
    T operator()();

    /*!
      Gibt den SQL-Typen dieses Attributs zurück. (z.B. QString -> TEXT, int -> Int).

      \return der SQL-Typen dieses Attributs.
      */
    QString sqlType() const;

    /*!
      Fügt diesem Attribut ein von ihm abhängiges Attribut hinzu.<br>
      Ändert sich anschließend dieses Attribut wird das \p dependingAttribute sich automatisch aktualisieren.
      */
    void addDependingAttribute(AttributeBase *dependingAttribute);

    bool isCalculating();

    /*!
      Berechnet den Wert des Attributs komplett neu.
      */
    void recalculateFromScratch();
protected:
    friend class TableModel<R, Table<R> >;
    friend class RecalculationTask<Attribute<T,R,C>,T>;


    /*!
      Setzt den Wert des Attributs auf \p value. Diese Funktion sollte nur für Datenbankattribute oder intern aufgerufen werden!
      */
    virtual void changeValue(const T value);

    /*!
      Setzt den Wert des Attributs auf \p value. Diese Funktion sollte nur für Datenbankattribute oder intern aufgerufen werden!
      */
    virtual void changeValue(const QVariant &value);

    /*!
      Wird aufgerufen, falls sich Attribute ändern, von denen dieses Attribut abhängt.<br>
      Ist das Attribut noch nicht initialisiert oder keine Updatefunktion gegeben, wird das Attribut komplett neu berechnet.<br>
      Sonst wird zunächst die Updatefunktion nach einem neuen Wert gefragt.<br>
      Kann diese aus den gegebenen Änderungen der geänderten Abhängigkeit keinen neuen Wert berechnen, wird das Attribut komplett neu berechnet.
      */
    void updateFromDependency();

    void waitForCalculationTask();

    /*!
      Ist eine Calculationfunction gesetzt, wird diese aufgerufen um den Wert des Attributs zu berechnen. Sonst wird ein leeres T() zurückgegeben.<br>
      Die Calculationfunction sollte den Wert nur berechnen und zurückgeben, ohne dabei schreibend auf irgendetwas zuzugreifen.
      */
    virtual T calculate() const;

    void setFuture(QFuture<T> future);

    void endCalculation();

    bool m_cacheInitialized; //!< true, wenn der Cache den korrekten Wert enthält.
    T m_value; //!< Der Cache für den Wert des Attributs.
    AttributeFutureWatcher* m_futureWatcher; //!< Der FutureWatcher dieser Klasse.

    C* m_calculator; //! Calculator für Calc-Funktion
    CalculateFunction m_calculateFunction; //!< Die Funktion zum (neu-)berechnen des Werts.
    UpdateFunction m_updateFunction; //!< Die Funktion zum Updaten des Attributs.
    QHash<QString,AttributeSpecificUpdateFunction> m_updateFunctions;

    QMutex m_mutex; //!< Ein Mutex zum Threadsicher machen...
    QMutex m_waitingMutex;
    QWaitCondition m_waitCondition;
    RecalculationTask<Attribute<T,R,C>, T>* m_currentTask;
    bool m_isCalculating;
};

//! Dieses Interface dient dazu, der template-Klasse AttributeFutureWatcher signals und slots, sowie ein Dasein als QObject zu ermöglichen.
/*!
  In Qt ist es nicht möglich dass template-Klassen QObjects sind oder mit Hilfe des Q_OBJECT Macros über signals und slots verfügen. Aus diesem Grund haben wir diese Elternklasse, von der AttributeFutureWatcher erben kann, die diese Funktionalitäten enthält und damit auch für seine Kindklasse bereitstellt.<br>
  Das "Interface" kümmert sich zudem um das Verbinden dieses FutureWatchers mit GUI Elementen.
  */
class AttributeFutureWatcher : public QObject
{
    Q_OBJECT
public:
    explicit AttributeFutureWatcher(AttributeBase* attribute);

    /*!
      Verbindet diesen FutureWatcher mit dem Label \p label.<br>
      Alle zukünftigen Änderungen werden dem Label mitgeteilt, sodass es sich automatisch anpassen kann.
      */
    void connectTo(QLabel *label);

    /*!
      Verbindet diesen FutureWatcher mit der LineEdit \p lineEdit.<br>
      Alle zukünftigen Änderungen werden der LineEdit mitgeteilt, sodass es sich automatisch anpassen kann.
      */
    void connectTo(QLineEdit *lineEdit);

signals:
    /*!
      Wird gesendet, wenn sich der Wert des Attributs ändert.

      \param value Der neue Wert.
      */
    void valueChanged(QString value);

protected slots:
    /*!
      Wird aufgerufen, wenn das Attribute signalisiert, dass es sich bald ändern wird.<br>
      Setzt alle verbundenen GUI-Elemente auf "Loading..."
      */
    void on_attribute_aboutToChange();

    void on_attribute_changed();

protected:
    AttributeBase* m_attribute;
};

template<class AttributeType, class ValueType>
class RecalculationTask : public Task
{
public:
    explicit RecalculationTask(AttributeType* m_attribute, int priority = QThread::InheritPriority);

    void execute();

private:
    AttributeType* m_attribute;
};

template<class T, class R, class C>
Attribute<T,R,C>::Attribute() :
    AttributeBase(),
    m_cacheInitialized(false),
    m_futureWatcher(0),
    m_calculator(0),
    m_calculateFunction(0),
    m_updateFunction(0),
    m_updateFunctions(QHash<QString,AttributeSpecificUpdateFunction>()),
    m_mutex(QMutex::Recursive),
    m_currentTask(0),
    m_isCalculating(false)
{
}

template<class T, class R, class C>
Attribute<T,R,C>::Attribute(const QString &name, const QString &displayName, AttributeOwner *owner) :
    AttributeBase(name, displayName, owner),
    m_cacheInitialized(false),
    m_futureWatcher(0),
    m_calculator(0),
    m_calculateFunction(0),
    m_updateFunction(0),
    m_updateFunctions(QHash<QString,AttributeSpecificUpdateFunction>()),
    m_mutex(QMutex::Recursive),
    m_currentTask(0),
    m_isCalculating(false)
{
}

template<class T, class R, class C>
Attribute<T,R,C>::~Attribute()
{
    if(m_futureWatcher)
    {
        m_futureWatcher->deleteLater();
    }
}

template<class T, class R, class C>
const AttributeVariant Attribute<T,R,C>::toVariant()
{
    AttributeVariant v;
    v.setValue(value());
    return v;
}

template<class T, class R, class C>
const QVariant Attribute<T,R,C>::displayVariant()
{
    QMutexLocker locker(&m_mutex); (void) locker;

    if(m_isCalculating) {
        return "Loading...";
    }

    AttributeVariant display = toVariant();
    display.setDisplayRole(AttributeVariant::MainWindow);
    QVariant variant = display.displayVariant();

    if (!variant.isNull()){
        return variant;
    }
    else{
        return display;
    }
}

template<class T, class R, class C>
const QString Attribute<T,R,C>::toString()
{
    return toVariant().toString();
}

template<class T, class R, class C>
AttributeFutureWatcher* Attribute<T,R,C>::futureWatcher()
{
    QMutexLocker locker(&m_mutex); (void) locker;

    if(m_futureWatcher == 0)
    {
        m_futureWatcher = new AttributeFutureWatcher(this);
    }
    return m_futureWatcher;
}

template<class T, class R, class C>
T Attribute<T,R,C>::calculate() const
{
    if(m_calculateFunction == 0)
    {
        return T();
    }

    T newValue = CALL_MEMBER_FN(static_cast<C*>(m_calculator),m_calculateFunction)();

    return newValue;
}

template<class T, class R, class C>
void Attribute<T,R,C>::updateFromDependency()
{
    recalculateFromScratch();

/*    m_lock.lock();
//    if(!m_cacheInitialized)
//    {
//    }
//    m_lock.unlock();

    m_lock.lockForWrite();
    AttributeBase *dependentAttribute = static_cast<AttributeBase*>(sender());
    AttributeSpecificUpdateFunction updateFunction = m_updateFunctions.value(dependentAttribute->name(), 0);
    QFuture<T> future;

    if(updateFunction != 0)
    {
        future = QtConcurrent::run(static_cast<C*>(m_calculator), updateFunction);
    }
    else
    {
        if(m_updateFunction == 0)
        {
            m_lock.unlock();
            recalculateFromScratch();
            return;
        }

        future = CALL_MEMBER_FN(static_cast<C*>(m_calculator),m_updateFunction)(dependentAttribute);
    }

    if(future.isRunning() || future.isResultReadyAt(0))
    {
        futureWatcher()->setFuture(future);
    }
    else
    {
        recalculateFromScratch(); // ungefaehr: if(!m_cacheInitialized) m_value = calculate();
    }

    m_lock.unlock();*/
}

template<class T, class R, class C>
void Attribute<T,R,C>::recalculateFromScratch()
{
    m_cacheInitialized = false;
    startCalculationTask(); // ungefaehr: if(!m_cacheInitialized) m_value = calculate();
}

template<class T, class R, class C>
bool Attribute<T,R,C>::isCalculating()
{
    return m_isCalculating;
}

template<class T, class R, class C>
void Attribute<T,R,C>::endCalculation()
{
//    m_mutex.lock();
//    m_waitingMutex.lock();
//    m_waitCondition.wakeAll();
//    m_waitingMutex.unlock();
//    m_isCalculating = false;
//    m_mutex.unlock();
}

template<class T, class R, class C>
void Attribute<T,R,C>::waitForCalculationTask()
{
//    m_mutex.lock();
//    if(m_isCalculating)
//    {
//        m_currentTask->increasePriority();
//        m_waitingMutex.lock();
//        m_mutex.unlock();

//        QThreadPool::globalInstance()->releaseThread();
//        m_waitCondition.wait(&m_waitingMutex);
//        QThreadPool::globalInstance()->reserveThread();

//        m_mutex.lock();
//        m_waitingMutex.unlock();
//    }
//    m_mutex.unlock();
}

template<class T, class R, class C>
AttributeFutureWatcher* Attribute<T,R,C>::startCalculationTask()
{
    m_mutex.lock();
    if(!m_cacheInitialized && !m_isCalculating)
    {
        m_isCalculating = true;
        m_currentTask = new RecalculationTask<Attribute<T,R,C>, T>(this);
//        connect(m_currentTask,SIGNAL(finished()),this,SLOT(endCalculation()));
        TaskScheduler::instance()->schedule(m_currentTask);
    }
    m_mutex.unlock();

    return futureWatcher();
}

template<class AttributeType, class ValueType>
void RecalculationTask<AttributeType,ValueType>::execute()
{
    const ValueType value = m_attribute->calculate();

    m_attribute->m_mutex.lock();
    m_attribute->changeValue(value);
    m_attribute->m_isCalculating = false;
    m_attribute->m_currentTask = 0;
    m_attribute->m_mutex.unlock();
}

template<class T, class R, class C>
const T Attribute<T,R,C>::value()
{
    m_mutex.lock();
    Task* task = m_currentTask;
    if(task)
    {
        m_mutex.unlock();
        task->waitForFinished();
        QWaitCondition w;
        QMutex m;
        m.lock();
        QThreadPool::globalInstance()->releaseThread();
        while(m_isCalculating && !m_cacheInitialized)
        {
            w.wait(&m,1);
        }
        QThreadPool::globalInstance()->reserveThread();
        m_mutex.lock();
    }
    bool change = false;
    if(!m_cacheInitialized && !m_isCalculating)
    {
        m_isCalculating = true;
        m_value = calculate();
        m_isCalculating = false;
        m_cacheInitialized = true;
        change = true;
    }
    m_mutex.unlock();

    return m_value;
}

template<class T, class R, class C>
void Attribute<T,R,C>::changeValue(const QVariant& value)
{
    changeValue(value.value<T>());
}

template<class T, class R, class C>
void Attribute<T,R,C>::changeValue(const T value)
{
    m_mutex.lock();

    bool change = true;
    QVariant v1;
    v1.setValue(m_value);
    QVariant v2;
    v2.setValue(value);
    change = v1 != v2;

    m_cacheInitialized = true;
    if(change)
    {
        m_value = value;
        m_mutex.unlock();
        if(m_emitChange)
        {
            emit changed();
        }
    }
    else
    {
        m_mutex.unlock();
    }
}


template<class T, class R, class C>
QString Attribute<T,R,C>::sqlType() const
{
    qWarning() << "Attribute::sqlType(): You shall not call sqlType on a non-database attribute!";
    return "";
}

template<class T, class R, class C>
void Attribute<T,R,C>::setCalculationFunction(C* calculator, CalculateFunction calculateFuntion)
{
    m_mutex.lock();
    m_calculateFunction = calculateFuntion;
    m_calculator = calculator;
    m_mutex.unlock();
}

template<class T, class R, class C>
void Attribute<T,R,C>::setUpdateFunction(C* calculator, UpdateFunction updateFunction)
{
    m_mutex.lock();
    m_updateFunction = updateFunction;
    m_calculator = calculator;
    m_mutex.unlock();
}

template<class T, class R, class C>
void Attribute<T,R,C>::setUpdateFunction(AttributeBase *attribute, AttributeSpecificUpdateFunction updateFunction)
{
    m_mutex.lock();
    m_updateFunctions.insert(attribute->name(), updateFunction);
    m_mutex.unlock();
}

template<class T, class R, class C>
void Attribute<T,R,C>::addDependingAttribute(AttributeBase *dependingAttribute)
{
    m_dependingAttributes.append(dependingAttribute);
    connect(this,SIGNAL(changed()),dependingAttribute,SLOT(updateFromDependency()));
    //connect(this,SIGNAL(changed()),this,SLOT(onChange()));
}

template<class AttributeType, class ValueType>
RecalculationTask<AttributeType,ValueType>::RecalculationTask(AttributeType* attribute, int priority) :
    Task(priority),
    m_attribute(attribute)
{
}

} // namespace Database

#define STRINGIZE(s) # s
#define XSTR(s) STRINGIZE(s)

#define DECLARE_ATTRIBUTE(Type, RowClassname, Name) \
Attribute<Type, RowClassname, RowClassname> *Name; \
Type calculate_ ## Name();

#define DECLARE_ATTRIBUTE_IN_CALC(Type, RowClassname, CalcClassName, Name) \
Attribute<Type, RowClassname, CalcClassName> *Name;

#define DECLARE_ATTRIBUTE_IN_CALC(Type, RowClassname, CalcClassName, Name) \
Attribute<Type, RowClassname, CalcClassName> *Name;

#define DECLARE_VIRTUAL_ATTRIBUTE_IN_CALC(Type, RowClassname, CalcClassName, Name) \
Attribute<Type, RowClassname, RowClassname> *Name; \
Type call_calculate_ ## Name(){ \
    return m_calc->calculate_ ## Name(); \
}

#define DECLARE_ATTRIBUTE_WITH_UPDATEFUNCTION(Type, RowClassname, Name) \
    Attribute<Type, RowClassname, RowClassname> *Name; \
    Type calculate_ ## Name(); \
    QFuture<Type>  updateIfPossible_ ## Name(AttributeBase *changedDependency); \
    Type update_ ## Name(AttributeBase *changedDependency);

#define IMPLEMENT_VIRTUAL_ATTRIBUTE_IN_CALC(Type, RowClassname, CalcClassName, Name, DisplayName) \
    Name = new Attribute<Type,RowClassname, RowClassname>(QString(XSTR(Name) "").toLower(),DisplayName,this); \
    Name->setCalculationFunction(this, & RowClassname::call_calculate_ ## Name); \
    registerAttribute(Name);

#define IMPLEMENT_ATTRIBUTE(Type, RowClassname, Name, DisplayName) \
    Name = new Attribute<Type,RowClassname, RowClassname>(QString(XSTR(Name) "").toLower(),DisplayName,this); \
    Name->setCalculationFunction(this, & RowClassname::calculate_ ## Name); \
    registerAttribute(Name);

#define IMPLEMENT_ATTRIBUTE_IN_CALC(Type, RowClassname, CalcClassName, CalcClassInstanceName, Name, DisplayName) \
    Name = new Attribute<Type,RowClassname, CalcClassName>(QString(XSTR(Name) "").toLower(),DisplayName,this); \
    Name->setCalculationFunction(CalcClassInstanceName, & CalcClassName::calculate_ ## Name); \
    registerAttribute(Name);

#define IMPLEMENT_ATTRIBUTE_WITH_UPDATEFUNCTION(Type, RowClassname, Name, DisplayName) \
    Name = new Attribute<Type,RowClassname, RowClassname>(QString(XSTR(Name) "").toLower(),DisplayName,this); \
    Name->setCalculationFunction(this, & RowClassname::calculate_ ## Name); \
    Name->setUpdateFunction(this, & RowClassname::updateIfPossible_ ## Name); \
    registerAttribute(Name);

#define IMPLEMENT_ATTRIBUTE_WITH_UPDATEFUNCTION_IN_CALC(Type, RowClassname, CalcClassName, CalcClassInstanceName, Name, DisplayName) \
    Name = new Attribute<Type,RowClassname, RowClassname>(QString(XSTR(Name) "").toLower(),DisplayName,this); \
    Name->setCalculationFunction(CalcClassInstanceName, & CalcClassName::calculate_ ## Name); \
    Name->setUpdateFunction(CalcClassInstanceName ,& CalcClassName::updateIfPossible_ ## Name); \
    registerAttribute(Name);

#endif // DATABASE_ATTRIBUTE_H
