#include "attribute.h"

#include "row.h"

#include <QLabel>
#include <QLineEdit>

namespace Database {

AttributeInterface::AttributeInterface() :
    QObject(),
    m_row(0)
{
}

AttributeInterface::AttributeInterface(Row *row) :
    QObject(row),
    m_row(row)
{
}

AttributeFutureWatcherInterface::AttributeFutureWatcherInterface(AttributeInterface* parent) :
    QObject(parent)
{
}

bool AttributeInterface::isDatabaseAttribute() const
{
    return false;
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
