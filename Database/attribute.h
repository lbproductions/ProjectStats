#ifndef DATABASE_ATTRIBUTE_H
#define DATABASE_ATTRIBUTE_H

#include <QObject>

#include <QPointer>
#include <QFuture>
#include <QReadWriteLock>
#include <QtConcurrentRun>
#include <QVariant>
#include <QFutureWatcher>

/*!
  Ruft auf dem Objekt \p object die Funktion \p ptrToMember auf.<br>
  \p object muss ein Pointer auf eine Klasse sein, und \p ptrToMember ein Pointer zu einer Funktion dieser Klasse.<br>

  \code Row *row; CALL_MEMBER_FN(row, &Row::set)("name",value);
  */
#define CALL_MEMBER_FN(object,ptrToMember)  ((*object).*(ptrToMember))

class QLabel;
class QLineEdit;

namespace Database {

class Row;

//! Dieses Interface dient dazu, der template-Klasse Attribute signals und slots, sowie ein Dasein als QObject zu ermöglichen.
/*!
  In Qt ist es nicht möglich dass template-Klassen QObjects sind oder mit Hilfe des Q_OBJECT Macros über signals und slots verfügen. Aus diesem Grund haben wir diese Elternklasse, von der Attribute erben kann, die diese Funktionalitäten enthält und damit auch für seine Kindklasse bereitstellt.
  */
class AttributeInterface : public QObject
{
    Q_OBJECT
public:
    /*!
      Wird benutzt um Rows als MetaType registrieren zu können. Niemals benutzen!
      */
    AttributeInterface();

    /*!
      Erstellt ein Attribut für die Row \p row.
      */
    explicit AttributeInterface(Row *row);

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
    virtual QString name() const = 0;

    /*!
      Gibt den SQL-Typen dieses Attributs zurück. (z.B. QString -> TEXT, int -> Int).

      \return der SQL-Typen dieses Attributs.
      */
    virtual QString sqlType() const = 0;

protected slots:
    /*!
      Berechnet den Wert des Attributs komplett neu.
      */
    virtual void recalculate() = 0;

    /*!
      Wird aufgerufen, falls sich Attribute ändern, von denen dieses Attribut abhängt.<br>
      Ist das Attribut noch nicht initialisiert oder keine Updatefunktion gegeben, wird das Attribut komplett neu berechnet.<br>
      Sonst wird zunächst die Updatefunktion nach einem neuen Wert gefragt.<br>
      Kann diese aus den gegebenen Änderungen der geänderten Abhängigkeit keinen neuen Wert berechnen, wird das Attribut komplett neu berechnet.
      */
    virtual void update() = 0;

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
    QPointer<Row> m_row; //!< Die Row, zu dem das Attribut gehört.
};

template<class T, class R>
class AttributeFutureWatcher;

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
template<class T, class R>
class Attribute : public AttributeInterface
{
public:
    typedef T (R::*CalculateFunction)(); //!< Die Signatur der Calculatefunction
    typedef QFuture<T> (R::*UpdateFunction)(AttributeInterface *changedDependency); //!< Die Signatur der Updatefunction
    typedef T (R::*AttributeSpecificUpdateFunction)();
    /*!
      Wird benutzt um Rows als MetaType registrieren zu können. Niemals benutzen!
      */
    Attribute();

    /*!
      Erstellt ein Attribut für die Row \p row.
      */
    Attribute(const QString &name, Row *row);

    /*!
      Gibt den Namen des Attributs zurück.

      \return Der Name des Attributs.
      */
    QString name() const;

    /*!
      Gibt den Wert des Attributs zurück.<br>
      Ist der Cache ungültig oder leer, wird er zuvor synchron neu berechnet.

      \return der Wert des Attributs.
      */
    virtual T value();

    /*!
      Setzt den Wert des Attributs auf \p value. Diese Funktion sollte nur für Datenbankattribute oder intern aufgerufen werden!
      */
    virtual void setValue(T value);

    /*!
      Startet im Hintergrund eine Neuberechnung des Attributs und
      gibt den AttributeFutureWatcher dieses Attributs zurück.

      \return der AttributeFutureWatcher dieses Attributs.
      */
    AttributeFutureWatcher<T,R> *calculateASync();

    /*!
      Gibt den AttributeFutureWatcher dieses Attributs zurück.

      \return der AttributeFutureWatcher dieses Attributs.
      */
    AttributeFutureWatcher<T,R> *futureWatcher();

    /*!
      Setzt die Calculationfunction dieses Attributs auf \p calculateFuntion.<br>
      Wie das geht, kann man sich gut bei bestehenden Rows abgucken.
      */
    virtual void setCalculationFunction(CalculateFunction calculateFuntion);

    /*!
      Setzt die Updatefunction dieses Attributs auf \p updateFunction.<br>
      Wie das geht, kann man sich gut bei bestehenden Rows abgucken.
      */
    void setUpdateFunction(UpdateFunction updateFunction);

    /*!
      Fügt eine Updatefunction \p updateFunction zu diesem Attribut hinzu.<br>
      Diese wird dann aufgerufen, wenn sich das Attribut \p attribute geändert hat.<br>
      */
    void setUpdateFunction(AttributeInterface* attribute, AttributeSpecificUpdateFunction updateFunction);

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
    void addDependingAttribute(AttributeInterface *dependingAttribute);

protected:
    friend class AttributeFutureWatcher<T,R>;

    /*!
      Wird aufgerufen, falls sich Attribute ändern, von denen dieses Attribut abhängt.<br>
      Ist das Attribut noch nicht initialisiert oder keine Updatefunktion gegeben, wird das Attribut komplett neu berechnet.<br>
      Sonst wird zunächst die Updatefunktion nach einem neuen Wert gefragt.<br>
      Kann diese aus den gegebenen Änderungen der geänderten Abhängigkeit keinen neuen Wert berechnen, wird das Attribut komplett neu berechnet.
      */
    void update();

    /*!
      Berechnet den Wert des Attributs komplett neu.
      */
    void recalculate();

    /*!
      Ist eine Calculationfunction gesetzt, wird diese aufgerufen um den Wert des Attributs zu berechnen. Sonst wird ein leeres T() zurückgegeben.<br>
      Die Calculationfunction sollte den Wert nur berechnen und zurückgeben, ohne dabei schreibend auf irgendetwas zuzugreifen.
      */
    virtual T calculate() const;

    bool m_cacheInitialized; //!< true, wenn der Cache den korrekten Wert enthält.
    T m_value; //!< Der Cache für den Wert des Attributs.
    QString m_name; //!< Der Name des Attributs
    CalculateFunction m_calculateFunction; //!< Die Funktion zum (neu-)berechnen des Werts.
    UpdateFunction m_updateFunction; //!< Die Funktion zum Updaten des Attributs.
    QReadWriteLock m_lock; //!< Ein Mutex um die Klasse Threadsicher zu machen.
    AttributeFutureWatcher<T,R> *m_futureWatcher; //!< Der FutureWatcher dieser Klasse.
    QHash<QString,AttributeSpecificUpdateFunction> m_updateFunctions;
};

//! Dieses Interface dient dazu, der template-Klasse AttributeFutureWatcher signals und slots, sowie ein Dasein als QObject zu ermöglichen.
/*!
  In Qt ist es nicht möglich dass template-Klassen QObjects sind oder mit Hilfe des Q_OBJECT Macros über signals und slots verfügen. Aus diesem Grund haben wir diese Elternklasse, von der AttributeFutureWatcher erben kann, die diese Funktionalitäten enthält und damit auch für seine Kindklasse bereitstellt.<br>
  Das "Interface" kümmert sich zudem um das Verbinden dieses FutureWatchers mit GUI Elementen.
  */
class AttributeFutureWatcherInterface : public QObject
{
    Q_OBJECT
public:
    explicit AttributeFutureWatcherInterface(AttributeInterface* parent);

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
    void valueChanged(QString toString);

private slots:
    /*!
      Wird aufgerufen, wenn sich der Wert des Attributs ändert, oder die aktuelle QFuture zu Ende berechnet hat.<br>
      Im ersten Fall wird einfach nur allen verbundenen GUI-Elementen die Änderung mitgeteilt.<br>
      Im zweiten Fall wird der Wert des Attributs aktualisiert und die Änderung anschließend bekannt gegeben.
      */
    virtual void update() = 0;

    /*!
      Wird aufgerufen, wenn das Attribute signalisiert, dass es sich bald ändern wird.<br>
      Setzt alle verbundenen GUI-Elemente auf "Loading..."
      */
    virtual void on_attributeAboutToChange() = 0;

private:
    /*!
      \return true falls die aktuelle QFuture gerade rechnet.
      */
    virtual bool isRunning() = 0;

    /*!
      Der Wert des Attributs.
      */
    virtual QString toString() = 0;

};

//! Ein AttributeFutureWatcher beobachtet Änderungen seines Attributs und dessen QFutures.
/*!
  Die Klasse ist vor allem dafür zuständig die QFutures seines Attributs zu beobachten und falls eine davon einen Wert liefert, diesen dem Attribut mitzuteilen.<br>
  Außerdem können sich GUI-Elemente mit dem FutureWatcher verbinden und so über zukünftige Änderungen informiert werden.
  */
template<class T, class R>
class AttributeFutureWatcher : public AttributeFutureWatcherInterface
{
public:
    /*!
      Gibt den internen QFutureWatcher zurück. Dieser kann zum Beispiel verwendet werden um selber auf Änderungen per signal-slot zu lauschen, oder aber an die aktuelle QFuture zu gelangen.<br>
      Die aktuelle QFuture muss jedoch nicht zwangsläufig auch die Future sein, die den zukünftigen Wert bestimmt.

      \return der interne QFutureWatcher
      */
    QFutureWatcher<T> *futureWatcher() const;

private:
    friend class Attribute<T,R>;

    /*!
      Erstellt einen FutureWatcher für das Attribut \p attribute.
      */
    explicit AttributeFutureWatcher(Attribute<T,R> *attribute);

    /*!
      Setzt die aktuelle QFuture auf \p future.
      */
    void setFuture(QFuture<T> future);

    /*!
      Wird aufgerufen, wenn sich der Wert des Attributs ändert, oder die aktuelle QFuture zu Ende berechnet hat.<br>
      Im ersten Fall wird einfach nur allen verbundenen GUI-Elementen die Änderung mitgeteilt.<br>
      Im zweiten Fall wird der Wert des Attributs aktualisiert und die Änderung anschließend bekannt gegeben.
      */
    void update();

    /*!
      Wird aufgerufen, wenn das Attribute signalisiert, dass es sich bald ändern wird.<br>
      Setzt alle verbundenen GUI-Elemente auf "Loading..."
      */
    void on_attributeAboutToChange();

    /*!
      \return true falls die aktuelle QFuture gerade rechnet. (Wird vom AttributeFutureWatcherInterface verwendet)
      */
    bool isRunning();

    /*!
      Der Wert des Attributs. (Wird vom AttributeFutureWatcherInterface verwendet)
      */
    QString toString();

    QPointer<Attribute<T,R> > m_attribute; //!< Das beobachtete Attribut.
    QPointer<QFutureWatcher<T> > m_futureWatcher; //!< Der interne QFutureWatcher.
};

template<class T, class R>
Attribute<T,R>::Attribute() :
    AttributeInterface(),
    m_cacheInitialized(false),
    m_name(QString()),
    m_calculateFunction(0),
    m_updateFunction(0),
    m_lock(QReadWriteLock::Recursive),
    m_futureWatcher(new AttributeFutureWatcher<T,R>(this))
{
}

template<class T, class R>
Attribute<T,R>::Attribute(const QString &name, Row *row) :
    AttributeInterface(row),
    m_cacheInitialized(false),
    m_name(name),
    m_calculateFunction(0),
    m_updateFunction(0),
    m_lock(QReadWriteLock::Recursive),
    m_futureWatcher(new AttributeFutureWatcher<T,R>(this))
{
}

template<class T, class R>
QString Attribute<T,R>::name() const
{
    return m_name;
}

template<class T, class R>
T Attribute<T,R>::operator()()
{
    return value();
}

template<class T, class R>
T Attribute<T,R>::value()
{
    m_lock.lockForWrite();
    if(!m_cacheInitialized)
    {
        if(!m_futureWatcher->isRunning())
        {
            m_value = calculate();
        }
        else
        {
            m_futureWatcher->m_futureWatcher->waitForFinished();
        }
        m_cacheInitialized = true;
    }

    m_lock.unlock();
    return m_value;
}

template<class T, class R>
void Attribute<T,R>::setValue(T value)
{
    m_lock.lockForWrite();
    bool change = m_value != value;
    m_cacheInitialized = true;
    if(change)
    {
        m_value = value;

        emit changed();
    }
    m_lock.unlock();
}

template<class T, class R>
AttributeFutureWatcher<T,R> *Attribute<T,R>::futureWatcher()
{
    return m_futureWatcher;
}

template<class T, class R>
AttributeFutureWatcher<T,R> *Attribute<T,R>::calculateASync()
{
    if(!m_cacheInitialized && !m_futureWatcher->isRunning())
    {
        m_lock.lockForWrite();
        emit aboutToChange();
        QFuture<T> future = QtConcurrent::run(this, &Attribute<T,R>::calculate);
        m_futureWatcher->setFuture(future);
        m_lock.unlock();
    }

    return m_futureWatcher;
}

template<class T, class R>
QString Attribute<T,R>::sqlType() const
{
    qWarning() << "Attribute::sqlType(): You shall not call sqlType on a non-database attribute!";
    return "";
}

template<class T, class R>
void Attribute<T,R>::setCalculationFunction(CalculateFunction calculateFuntion)
{
    m_lock.lockForWrite();
    m_calculateFunction = calculateFuntion;
    m_lock.unlock();
}

template<class T, class R>
void Attribute<T,R>::setUpdateFunction(UpdateFunction updateFunction)
{
    m_lock.lockForWrite();
    m_updateFunction = updateFunction;
    m_lock.unlock();
}

template<class T, class R>
void Attribute<T,R>::setUpdateFunction(AttributeInterface *attribute, AttributeSpecificUpdateFunction updateFunction)
{
    m_lock.lockForWrite();
    m_updateFunctions.insert(attribute->name(), updateFunction);
    m_lock.unlock();
}

template<class T, class R>
T Attribute<T,R>::calculate() const
{
    if(m_calculateFunction == 0)
    {
        return T();
    }

    T newValue = CALL_MEMBER_FN(static_cast<R*>(m_row.data()),m_calculateFunction)();

    return newValue;
}

template<class T, class R>
void Attribute<T,R>::update()
{
    if(!m_cacheInitialized)
    {
        recalculate();
        return;
    }

    m_lock.lockForWrite();
    AttributeInterface *dependentAttribute = static_cast<AttributeInterface*>(sender());
    AttributeSpecificUpdateFunction updateFunction = m_updateFunctions.value(dependentAttribute->name(), 0);
    QFuture<T> future;

    if(updateFunction != 0)
    {
        future = QtConcurrent::run(static_cast<R*>(m_row.data()), updateFunction);
    }
    else
    {
        if(m_updateFunction == 0)
        {
            m_lock.unlock();
            recalculate();
            return;
        }

        future = CALL_MEMBER_FN(static_cast<R*>(m_row.data()),m_updateFunction)(dependentAttribute);
    }

    if(future.isRunning() || future.isResultReadyAt(0))
    {
        m_futureWatcher->setFuture(future);
    }
    else
    {
        recalculate(); // ungefaehr: if(!m_cacheInitialized) m_value = calculate();
    }

    m_lock.unlock();
}

template<class T, class R>
void Attribute<T,R>::recalculate()
{
    m_cacheInitialized = false;
    calculateASync(); // ungefaehr: if(!m_cacheInitialized) m_value = calculate();
}

template<class T, class R>
void Attribute<T,R>::addDependingAttribute(AttributeInterface *dependingAttribute)
{
    connect(this,SIGNAL(changed()),dependingAttribute,SLOT(update()));
}

template<class T, class R>
AttributeFutureWatcher<T,R>::AttributeFutureWatcher(Attribute<T,R> *parent) :
    AttributeFutureWatcherInterface(parent),
    m_attribute(parent),
    m_futureWatcher(new QFutureWatcher<T>())
{
    connect(m_futureWatcher,SIGNAL(finished()),this,SLOT(update()));
    connect(m_attribute,SIGNAL(changed()),this,SLOT(update()));
    connect(m_attribute,SIGNAL(aboutToChange()),this,SLOT(on_attributeAboutToChange()));
}

template<class T, class R>
void AttributeFutureWatcher<T,R>::setFuture(QFuture<T> future)
{
    m_futureWatcher->setFuture(future);

    if(future.isFinished())
    {
        update();
    }
}
template<class T, class R>
QFutureWatcher<T> *AttributeFutureWatcher<T,R>::futureWatcher() const
{
    return m_futureWatcher();
}

template<class T, class R>
void AttributeFutureWatcher<T,R>::on_attributeAboutToChange()
{
    emit valueChanged("Loading...");
}

template<class T, class R>
void AttributeFutureWatcher<T,R>::update()
{
    if(m_futureWatcher->future().isResultReadyAt(0))
    {
        if(sender() == m_futureWatcher)
        {
            T value = m_futureWatcher->future().result();
            m_attribute->setValue(value);
            QVariant v;
            v.setValue(value);
            emit valueChanged(v.toString());
        }
        else
        {
            T value = m_attribute->value();
            QVariant v;
            v.setValue(value);
            emit valueChanged(v.toString());
        }
    }
}

template<class T, class R>
bool AttributeFutureWatcher<T,R>::isRunning()
{
    return m_futureWatcher->isRunning();
}

template<class T, class R>
QString AttributeFutureWatcher<T,R>::toString()
{
    QVariant v;
    v.setValue(m_attribute->value());
    return v.toString();
}

} // namespace Database

#define DECLARE_ATTRIBUTE(Type, RowClassname, Name) \
Attribute<Type, RowClassname> *Name; \
Type calculate_ ## Name();

#define DECLARE_ATTRIBUTE_WITH_UPDATEFUNCTION(Type, RowClassname, Name) \
    Attribute<Type, RowClassname> *Name; \
    Type calculate_ ## Name(); \
    QFuture<Type>  updateIfPossible_ ## Name(AttributeInterface *changedDependency); \
    Type update_ ## Name(AttributeInterface *changedDependency);

#define IMPLEMENT_ATTRIBUTE(Type, RowClassname, Name) \
    Name = new Attribute<Type,RowClassname>("Name",this); \
    Name->setCalculationFunction(& RowClassname::calculate_ ## Name); \
    registerAttribute(Name);

#define IMPLEMENT_ATTRIBUTE_WITH_UPDATEFUNCTION(Type, RowClassname, Name) \
    Name = new Attribute<Type,RowClassname>("Name",this); \
    Name->setCalculationFunction(& RowClassname::calculate_ ## Name); \
    Name->setUpdateFunction(& RowClassname::updateIfPossible_ ## Name); \
    registerAttribute(Name);

#endif // DATABASE_ATTRIBUTE_H
