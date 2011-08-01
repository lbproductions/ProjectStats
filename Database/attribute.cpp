#include "attribute.h"

#include "row.h"

#include <QLabel>
#include <QLineEdit>

#include <Database/player.h>

namespace Database {


Changeable::Changeable(QObject *parent) :
    QObject(parent)
{
}

const QString Changeable::toString()
{
    return QString();
}

AttributeOwner::AttributeOwner(QObject *parent) :
    Changeable(parent)
{
}

AttributeBase::AttributeBase() :
    Changeable(),
    m_owner(0),
    m_name(QString()),
    m_displayName(QString()),
    m_role(Qt::DisplayRole),
    m_emitChange(true)
{
}

AttributeBase::AttributeBase(const QString &name, const QString &displayName, AttributeOwner *row) :
    Changeable(row),
    m_owner(row),
    m_name(name),
    m_displayName(displayName),
    m_role(Qt::DisplayRole),
    m_emitChange(true)
{
}

AttributeOwner *AttributeBase::owner() const
{
    return m_owner;
}

int AttributeBase::role() const
{
    return m_role;
}

void AttributeBase::changeValue(int value)
{
    changeValue(QVariant(value));
}

void AttributeBase::setRole(int role)
{
    m_role = role;
}

QString AttributeBase::name() const
{
    return m_name;
}

QString AttributeBase::displayName() const
{
    return m_displayName;
}

bool AttributeBase::isDatabaseAttribute() const
{
    return false;
}

void AttributeBase::changeValue(QVariant value, bool /*updateDatabase*/)
{
    changeValue(value);
}

void AttributeBase::setDisplayRole(AttributeVariant::DisplayRole role){
    m_displayRole = role;
}

void AttributeBase::setEmitChange(bool check)
{
    m_emitChange = check;
}

void AttributeBase::onChange()
{
    qDebug() << "Attribute<T,R,C>::onChange():" << this->m_name << "changed. Will now update:";
    foreach(AttributeBase* a, m_dependingAttributes)
    {
        qDebug() << "Attribute<T,R,C>::onChange():" << a->name();
    }
}

AttributeVariant::DisplayRole AttributeBase::displayRole(){
    return m_displayRole;
}

AttributeFutureWatcher::AttributeFutureWatcher(AttributeBase* attribute) :
    QObject(attribute),
    m_attribute(attribute)
{
    connect(m_attribute,SIGNAL(changed()),this,SLOT(on_attribute_changed()));
    connect(m_attribute,SIGNAL(aboutToChange()),this,SLOT(on_attribute_aboutToChange()));
}

void AttributeFutureWatcher::on_attribute_aboutToChange()
{
    emit valueChanged("Loading...");
}

void AttributeFutureWatcher::on_attribute_changed()
{
    emit valueChanged(m_attribute->toString());
}

void AttributeFutureWatcher::connectTo(QLabel *label)
{
    if(m_attribute->isCalculating())
    {
	label->setText("Loading...");
    }
    else
    {
        label->setText(m_attribute->toString());
    }

    connect(this,SIGNAL(valueChanged(QString)),label,SLOT(setText(QString)));
}

void AttributeFutureWatcher::connectTo(QLineEdit *lineEdit)
{
    if(m_attribute->isCalculating())
    {
	lineEdit->setText("Loading...");
    }
    else
    {
        lineEdit->setText(m_attribute->toString());
    }

    connect(this,SIGNAL(valueChanged(QString)),lineEdit,SLOT(setText(QString)));
}

void AttributeBase::emitChanged()
{
    emit changed();
}

} // namespace Database
