#include "mainwindow.h"

#include <Gui/Misc/rowlist.h>

#include <Database/table.h>

#include <QMessageBox>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_tabwidget(new QTabWidget(this)),
    m_button(new QPushButton("Open table in new window", this)),
    m_openWindows(QList<QWidget*>())
{
    QWidget *w = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(w);

    foreach(Database::TableBase *table, Database::Database::instance()->tables())
    {
        Gui::Misc::RowList *rowList = new Gui::Misc::RowList(table->model(), m_tabwidget);
        m_tabwidget->addTab(rowList, table->name());
    }

    layout->addWidget(m_tabwidget);
    layout->addWidget(m_button);
    connect(m_button,SIGNAL(clicked()), this,SLOT(on_button_clicked()));
    w->setLayout(layout);
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    foreach(QWidget *w , m_openWindows)
    {
        w->deleteLater();
    }
}

void MainWindow::on_button_clicked()
{
    Gui::Misc::RowList *rowList1 = static_cast<Gui::Misc::RowList *>(m_tabwidget->currentWidget());
    Gui::Misc::RowList *rowList = new Gui::Misc::RowList(rowList1->model());
    rowList->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int count = QThreadPool::globalInstance()->activeThreadCount();
    if(count > 0)
    {
        QMessageBox msg;
        msg.setText(QString("There are %1 background tasks still running. We will wait for them to finish.").arg(count));
        msg.exec();
        QThreadPool::globalInstance()->waitForDone();
    }

    event->accept();
}
