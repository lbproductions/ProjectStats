#include "headerlabel.h"

using namespace Gui::Misc;

HeaderLabel::HeaderLabel(QString text, QWidget *parent) :
    QLabel(parent)
{
    this->setText(text);
}
