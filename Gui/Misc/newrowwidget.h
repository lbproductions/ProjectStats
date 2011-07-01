#ifndef NEWROWWIDGET_H
#define NEWROWWIDGET_H

#include <QDialog>
#include <QPointer>
#include <Database/row.h>

namespace Ui {
    class NewRowWidget;
}

class NewRowWidget : public QDialog
{
    Q_OBJECT

public:
    explicit NewRowWidget(Database::Row* row, QWidget *parent = 0);
    ~NewRowWidget();

private slots:
    void on_pushButtonCreate_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::NewRowWidget *ui;

    QPointer<Database::Row> m_row;
};

#endif // NEWROWWIDGET_H
