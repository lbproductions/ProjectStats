#include "attribute.h"

#include "row.h"

#include <QLabel>
#include <QLineEdit>

namespace Database {

AttributeOwner::AttributeOwner(QObject *parent) :
    QObject(parent)
{
}

AttributeInterface::AttributeInterface() :
    QObject(),
    m_owner(0)
{
}

AttributeInterface::AttributeInterface(const QString &name, AttributeOwner *row) :
    QObject(row),
    m_owner(row),
    m_name(name)
{
}

QString AttributeInterface::name() const
{
    return m_name;
}

bool AttributeInterface::isDatabaseAttribute() const
{
    return false;
}

AttributeFutureWatcherInterface::AttributeFutureWatcherInterface(AttributeInterface* parent) :
    QObject(parent)
{
}

void AttributeFutureWatcherInterface::on_attributeAboutToChange()
{
    emit valueChanged("Loading...");
}

void AttributeFutureWatcherInterface::connectTo(QLabel *label)
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

void AttributeFutureWatcherInterface::connectTo(QLineEdit *lineEdit)
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
