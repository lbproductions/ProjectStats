#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Database/drinks.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_drink = Database::Drinks::instance()->rowById(5);
    Database::AttributeFutureWatcher<QString,Database::Drink> *future = m_drink->name.futureWatcher();
    future->connectTo(ui->labelName);
    future->connectTo(ui->lineEditName);

    future = m_drink->type.futureWatcher();
    future->connectTo(ui->labelType);
    future->connectTo(ui->lineEditType);

    future = m_drink->test.futureWatcher();
    future->connectTo(ui->labelTest);
    future->connectTo(ui->labelTestB);

    future = m_drink->test2.futureWatcher();
    future->connectTo(ui->labelTest2);
    future->connectTo(ui->labelTest2B);
 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEditName_editingFinished()
{
    m_drink->name.setValue(ui->lineEditName->text());
}

void MainWindow::on_lineEditType_editingFinished()
{
    m_drink->type.setValue(ui->lineEditType->text());
}
