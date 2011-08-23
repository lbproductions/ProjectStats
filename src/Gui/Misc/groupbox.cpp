#include "groupbox.h"

#include <QVBoxLayout>

using namespace Gui::Misc;

GroupBox::GroupBox(QWidget *contentWidget, QWidget *parent) :
    QFrame(parent)
{
    this->setStyleSheet("Gui--Misc--GroupBox {"
                        "background: transparent;"
                        "border: 5px transparent;"
                        "border-image: url(:/graphics/styles/mac/groupbox/fullscreen/background) 5px 5px 5px 5px;"
                        "margin: 0px;"
                        "padding: -5px;"
                        "}");
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(contentWidget);
    this->setLayout(layout);
}
