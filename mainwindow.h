#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;

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
    void on_button_clicked();

private:
    QTabWidget *m_tabwidget;
    QPushButton *m_button;

    QList<QWidget*> m_openWindows;
};

#endif // MAINWINDOW_H
