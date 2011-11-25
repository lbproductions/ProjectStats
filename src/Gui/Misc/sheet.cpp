#include "sheet.h"

#include <QHBoxLayout>

using namespace Gui::Misc;

Sheet::Sheet(QWidget *parent) :
    QFrame(parent),
    m_widget(0)
{
    this->setStyleSheet("Gui--Misc--Sheet {"
                     "background: transparent;"
                     "border: 8 8 8 8 transparent;"
                     "border-image: url(:/graphics/images/sheetbackground) 8 8 8 8;"
                     "margin: 20px;"
                     "padding: 8 8 8 8;"
                 "}");
    QHBoxLayout* layout = new QHBoxLayout(this);
    setLayout(layout);
}

void Sheet::setWidget(QWidget *widget)
{
    if(m_widget)
    {
        m_widget->setVisible(false);
    }

    m_widget = widget;
    layout()->addWidget(widget);
}
