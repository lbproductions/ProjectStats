#include "clickablelabel.h"

#include <QMouseEvent>

using namespace Gui::Misc;

ClickableLabel::ClickableLabel(QWidget *parent) :
    QLabel(parent)
{
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent *event)
{
    QLabel::mouseReleaseEvent(event);

    if(event->button() == Qt::LeftButton)
    {
	emit clicked();
    }
}

void ClickableLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    QLabel::mouseReleaseEvent(event);

    if(event->button() == Qt::LeftButton)
    {
        emit doubleClicked();
    }
}
