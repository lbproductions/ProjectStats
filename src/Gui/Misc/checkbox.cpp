#include "checkbox.h"

using namespace Gui::Misc;

CheckBox::CheckBox(QString text, QWidget *parent) :
    QCheckBox(text,parent)
{
    connect(this,SIGNAL(toggled(bool)),this,SLOT(onStateChanged()));

    this->setText("");
}

void CheckBox::onStateChanged(){
    emit checkStateChanged(this,this->isChecked());
}
