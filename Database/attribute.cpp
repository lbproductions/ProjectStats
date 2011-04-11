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
    m_owner(0)
{
}

AttributeBase::AttributeBase(const QString &name, AttributeOwner *row) :
    QObject(row),
    m_owner(row),
    m_name(name)
{
}

QString AttributeBase::name() const
{
    return m_name;
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
