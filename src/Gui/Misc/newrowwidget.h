#ifndef NEWROWWIDGET_H
#define NEWROWWIDGET_H

#include <QDialog>

#include <LBDatabase/LBDatabase.h>

namespace Ui {
    class NewRowWidget;
}

namespace Database {
    class PSRow;
}

class NewRowWidget : public QDialog
{
    Q_OBJECT

public:
    explicit NewRowWidget(Database::PSRow* row, QWidget *parent = 0);
    ~NewRowWidget();

private slots:
    void on_pushButtonCreate_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::NewRowWidget *ui;

    Database::PSRow* m_row;
};

#endif // NEWROWWIDGET_H
