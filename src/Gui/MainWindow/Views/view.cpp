#include "view.h"

#include "../mainwindow.h"

using namespace Gui::MainWindow::Views;

View::View(MainWindow *parent) :
    QWidget(parent),
    m_mainWindow(parent)
{
}
