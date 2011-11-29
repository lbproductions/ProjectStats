#include "progressinfoboxwidget.h"

#include <QHBoxLayout>
#include <QSpacerItem>

#include <Gui/Misc/valuelabel.h>
#include <Gui/Misc/psprogressbar.h>

using namespace Gui::Misc;

ProgressInfoBoxWidget::ProgressInfoBoxWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setLayout(new QHBoxLayout());

    m_labelLeft = new ValueLabel();
    m_progressbar = new PSProgressBar(this);


    layout()->addWidget(m_labelLeft);
    layout()->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding));
    layout()->addWidget(m_progressbar);

}

void ProgressInfoBoxWidget::setFullscreen()
{
    m_progressbar->setFullscreen();
}

void ProgressInfoBoxWidget::setNormalMode()
{

}

PSProgressBar* ProgressInfoBoxWidget::progressbar()
{
    return m_progressbar;
}

void ProgressInfoBoxWidget::setLeftLabelText(QString text)
{
    m_labelLeft->setText(text);
}

