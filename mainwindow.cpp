#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Database/drinks.h>

#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_drink = Database::Drinks::instance()->rowById(5);
    Database::AttributeFutureWatcher<QString,Database::Drink> *future = m_drink->name.calculateASync();
    future->connectTo(ui->labelName);
    future->connectTo(ui->lineEditName);

    future = m_drink->type.calculateASync();
    future->connectTo(ui->labelType);
    future->connectTo(ui->lineEditType);

    future = m_drink->test.calculateASync();
    future->connectTo(ui->labelTest);
    future->connectTo(ui->labelTestB);

    future = m_drink->test2.calculateASync();
    future->connectTo(ui->labelTest2);
    future->connectTo(ui->labelTest2B);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_lineEditName_editingFinished()
{
    m_drink->name.setValue(ui->lineEditName->text());
}

void MainWindow::on_lineEditType_editingFinished()
{
    m_drink->type.setValue(ui->lineEditType->text());
}

void MainWindow::on_pushButton_clicked()
{
    for(int j = 0; j < 500; ++j)
    {
        QtConcurrent::run(this, &MainWindow::threadTest);
    }
}

void MainWindow::threadTest()
{
    for(int i = 1; i <= 10; ++i)
    {
        m_drink->name.setValue("name"+QString::number(i));
        m_drink->type.setValue("type"+QString::number(i));
    }
}
