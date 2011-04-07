#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

namespace Database {
    class Drink;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void closeEvent(QCloseEvent *event);

private slots:
    void on_lineEditType_editingFinished();

    void on_lineEditName_editingFinished();

    void on_pushButton_clicked();

private:
    void threadTest();
    Ui::MainWindow *ui;
    Database::Drink *m_drink;
};

#endif // MAINWINDOW_H
