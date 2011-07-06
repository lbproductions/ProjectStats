#include "attribute.h"

#include "row.h"

#include <QLabel>
#include <QLineEdit>

#include <Database/player.h>

namespace Database {

AttributeOwner::AttributeOwner(QObject *parent) :
    QObject(parent)
{
}

AttributeBase::AttributeBase() :
    QObject(),
    m_owner(0),
    m_role(Qt::DisplayRole)
{
}

AttributeBase::AttributeBase(const QString &name, const QString &displayName, AttributeOwner *row) :
    QObject(row),
    m_owner(row),
    m_name(name),
    m_displayName(displayName),
    m_role(Qt::DisplayRole)
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

void AttributeBase::setValue(int value)
{
    setValue(QVariant(value));
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

void AttributeBase::setValue(QVariant value, bool /*updateDatabase*/)
{
    setValue(value);
}

AttributeFutureWatcherBase::AttributeFutureWatcherBase() :
    QObject()
{
}

void AttributeFutureWatcherBase::on_attributeAboutToChange()
{
    emit valueChanged("Loading...");
}

void AttributeFutureWatcherBase::connectTo(QLabel *label)
{
    if(isRunning())
    {
	label->setText("Loading...");
    }
    else
    {
	label->setText(toString());
    }

    //connect(this,SIGNAL(valueChanged(QString)),label,SLOT(setText(QString)));
    connect(this,SIGNAL(valueChanged(QString)),this,SLOT(check(QString)));
}

void AttributeFutureWatcherBase::connectTo(QLineEdit *lineEdit)
{
    if(isRunning())
    {
	lineEdit->setText("Loading...");
    }
    else
    {
	lineEdit->setText(toString());
    }

    connect(this,SIGNAL(valueChanged(QString)),lineEdit,SLOT(setText(QString)));
}

void AttributeBase::emitChanged()
{
    emit changed();
}

void AttributeFutureWatcherBase::check(QString a){
    qDebug() << a;
}

void AttributeFutureWatcherBase::updateKey(QVariant variant){

}

} // namespace Database
