#ifndef DATABASE_DATABASEATTRIBUTE_H
#define DATABASE_DATABASEATTRIBUTE_H

#include "attribute.h"

#include "row.h"

#include <QVariant>

#if QT_VERSION >= 0x050000
#include <QtConcurrent/QtConcurrent>
#else
#include <QtConcurrentRun>
#endif

namespace Database {

template<class R>
class Table;

//! Ein DatabaseAttribute ist ein Attribut, das "physikalisch" in der Datenbank liegt.
/*!
  Die Klasse implementiert setValue() und calculate() so neu, dass alle Zugriffe an die Datenbank weitergeleitet werden.<br>
  Aus diesem Grund ist es selberverständlich nicht möglich einem Databaseattribut eine Calculationfunction zu geben.<br>
  <br>
  Außerdem sei angemerkt, dass alle schreibenden Zugriffe auf die Datenbank in einem eigenen Thread gestartet werden.
  */
template<class T, class R, class C>
class DatabaseAttribute : public Attribute<T,R,C>
{
public:
    typedef T (Row::*CalculateFunction)();

    /*!
      Wird benutzt um Rows als MetaType registrieren zu können. Niemals benutzen!
      */
    DatabaseAttribute();

    /*!
      Erstellt ein Datenbankattribut mit dem Namen \p name, das zur Row \p row gehört.
      */
    DatabaseAttribute(const QString &name, const QString &displayName, Row *row);

    /*!
      Setzt den Wert des Attributs auf \p value. Der Wert wird außerdem von einem neu gestarteten Thread in die Datenbank geschrieben.
      */
    void setValue(T value);

    /*!
      Setzt den Wert des Attributs auf \p value. Der Wert wird in die Datenbank geschrieben, wenn \p updateDatabase \c true ist.
      */
    void setValue(T value, bool updateDatabase);

    /*!
      Diese Funktion tut nichts außer eine Warning auszugeben.
      */
    void setCalculationFunction(CalculateFunction calculateFuntion);

    /*!
      \return true
      */
    bool isDatabaseAttribute() const;

    /*!
      Gibt den SQL-Typen dieses Attributs zurück. (z.B. QString -> TEXT, int -> Int).

      \return der SQL-Typen dieses Attributs.
      */
    QString sqlType() const;

protected:
    friend class Table<R>;

    void changeValue(QVariant value, bool updateDatabase);

    /*!
      Liest den Wert aus der Datenbank aus.<br>

      \return Der Wert des Attributs in der Datenbank.
      */
    T calculate() const;
};

template<class T, class R, class C>
DatabaseAttribute<T,R,C>::DatabaseAttribute() :
    Attribute<T,R,C>()
{
}

template<class T, class R, class C>
DatabaseAttribute<T,R,C>::DatabaseAttribute(const QString &name, const QString &displayName, Row *row) :
    Attribute<T,R,C>(name,displayName, row)
{
}

template<class T, class R, class C>
void DatabaseAttribute<T,R,C>::setValue(T value, bool updateDatabase)
{
    changeValue(value, updateDatabase);
}

template<class T, class R, class C>
void DatabaseAttribute<T,R,C>::setValue(T value)
{
    setValue(value, true);
}

template<class T, class R, class C>
void DatabaseAttribute<T,R,C>::changeValue(QVariant value, bool updateDatabase)
{
    QVariant v;
    v.setValue(Attribute<T,R,C>::m_value);

    if(updateDatabase)
    {
        Attribute<T,R,C>::changeValue(value.value<T>());
        updateDatabase = value != v;
        QtConcurrent::run(static_cast<Row*>(Attribute<T,R,C>::m_owner), &Row::set, Attribute<T,R,C>::m_name, value);
    }
    else
    {
        Attribute<T,R,C>::changeValue(value.value<T>());/*
        Attribute<T,R,C>::m_cacheInitialized = true;
        Attribute<T,R,C>::m_value = value.value<T>();*/
    }
    //Attribute<T,R>::m_row->set(Attribute<T,R>::m_name, value);
}

template<class T, class R, class C>
void DatabaseAttribute<T,R,C>::setCalculationFunction(CalculateFunction /*calculateFuntion*/)
{
    qWarning() << "DatabaseAttribute<T>::setCalculationFunction: You may not invoke this method on a DatabaseAttribute!";
}

template<class T, class R, class C>
T DatabaseAttribute<T,R,C>::calculate() const
{
    return QVariant(static_cast<Row*>(Attribute<T,R,C>::m_owner)->get(Attribute<T,R,C>::m_name)).value<T>();
}

template<class T, class R, class C>
bool DatabaseAttribute<T,R,C>::isDatabaseAttribute() const
{
    return true;
}

template<class T, class R, class C>
QString DatabaseAttribute<T,R,C>::sqlType() const
{
    T t;
    QVariant v;
    v.setValue(t);
    switch(v.type())
    {

    case QVariant::DateTime:
    case QVariant::Date:
        return "DATETIME";
        break;
    case QVariant::Double:
        return "DOUBLE";
        break;
    case QVariant::Int:
        return "INTEGER";
        break;
    case QVariant::String:
    case QVariant::Pixmap:
        return "TEXT";
        break;
    case QVariant::Invalid:
    case QVariant::BitArray:
    case QVariant::Bitmap:
    case QVariant::Bool:
    case QVariant::Brush:
    case QVariant::ByteArray:
    case QVariant::Char:
    case QVariant::Color:
    case QVariant::Cursor:
    case QVariant::EasingCurve:
    case QVariant::Font:
    case QVariant::Hash:
    case QVariant::Icon:
    case QVariant::Image:
    case QVariant::KeySequence:
    case QVariant::Line:
    case QVariant::LineF:
    case QVariant::List:
    case QVariant::Locale:
    case QVariant::LongLong:
    case QVariant::Map:
    case QVariant::Matrix:
    case QVariant::Transform:
    case QVariant::Matrix4x4:
    case QVariant::Palette:
    case QVariant::Pen:
    case QVariant::Point:
    case QVariant::PointF:
    case QVariant::Polygon:
    case QVariant::Quaternion:
    case QVariant::Rect:
    case QVariant::RectF:
    case QVariant::RegExp:
    case QVariant::Region:
    case QVariant::Size:
    case QVariant::SizeF:
    case QVariant::SizePolicy:
    case QVariant::StringList:
    case QVariant::TextFormat:
    case QVariant::TextLength:
    case QVariant::Time:
    case QVariant::UInt:
    case QVariant::ULongLong:
    case QVariant::Url:
    case QVariant::Vector2D:
    case QVariant::Vector3D:
    case QVariant::Vector4D:
    case QVariant::UserType:
    default:
        break;
    }

    qWarning() << "Attribute::sqlType(): Unkown type!";
    return "";
}

} // namespace Database

#define STRINGIZE(s) # s
#define XSTR(s) STRINGIZE(s)

#define DECLARE_DATABASEATTRIBUTE(Type, RowClassname, Name) \
    DatabaseAttribute<Type,RowClassname, RowClassname> *Name;

#define IMPLEMENT_DATABASEATTRIBUTE(Type, RowClassname, Name, DisplayName) \
    Name = new DatabaseAttribute<Type,RowClassname,RowClassname>(XSTR(Name) "",DisplayName, this); \
    registerAttribute(Name);

#endif // DATABASE_DATABASEATTRIBUTE_H
