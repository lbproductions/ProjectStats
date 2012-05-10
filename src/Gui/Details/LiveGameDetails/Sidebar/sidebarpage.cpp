#include "sidebarpage.h"

using namespace Gui::Details::LiveGameDetails::Sidebar;

SidebarPage::SidebarPage(QWidget *parent) :
    QWidget(parent)
{
    QPalette palette = this->palette();
    QPixmap pixmap;
    pixmap.load(":/graphics/styles/mac/toolbar/fullscreen/sidebar_background_fullscreen");
    palette.setBrush(QPalette::Window,QBrush(pixmap));
    this->setPalette(palette);
}
