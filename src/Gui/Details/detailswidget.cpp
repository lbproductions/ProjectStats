#include "detailswidget.h"

#include <Database/row.h>

using namespace Gui::Details;

DetailsWidget::DetailsWidget(Database::Row *row, QWidget *parent) :
    QWidget(parent),
    m_row(row),
    m_mayBeEditable(false)
{
    setAttribute(Qt::WA_DeleteOnClose);
}

Database::Row *DetailsWidget::row() const
{
    return m_row;
}

void DetailsWidget::setDescription(QString description){
    m_description = description;
}

QString DetailsWidget::description(){
    return m_description;
}

void DetailsWidget::setTitle(QString title){
    m_title = title;
}

QString DetailsWidget::title(){
    return m_title;
}

void DetailsWidget::setEditable(bool editable){
    m_editable = editable;
}

bool Gui::Details::DetailsWidget::isEditable() const
{
    return m_editable;
}

bool Gui::Details::DetailsWidget::mayBeEditable() const
{
    return m_mayBeEditable;
}
