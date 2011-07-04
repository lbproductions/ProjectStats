#include "rowwindow.h"

#include <QScrollArea>

#include <Database/row.h>
#include <Gui/Details/rowwidget.h>
#include <Gui/Misc/macwindowcontroller.h>

using namespace Gui::Details;

RowWindow::RowWindow(QWidget *parent):
    QMainWindow(parent)
{
}

RowWindow::RowWindow(Database::Row* row, QWidget *parent) :
    QMainWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    QPalette p = palette();
    p.setColor(QPalette::Window, QColor(255,255,255));
    setPalette(p);

    m_rowWidget = row->rowWidget();

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(m_rowWidget);
    setCentralWidget(scrollArea);
    setUpFullScreenButton(this);
}