#include "attribute.h"

#include "row.h"

#include <QLabel>
#include <QLineEdit>

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

int AttributeBase::role() const
{
    return m_role;
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

AttributeFutureWatcherBase::AttributeFutureWatcherBase(AttributeBase* parent) :
    QObject(parent)
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

    connect(this,SIGNAL(valueChanged(QString)),label,SLOT(setText(QString)));
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

} // namespace Database
