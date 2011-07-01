#ifndef NEWLEAGUEDIALOG_H
#define NEWLEAGUEDIALOG_H

#include <QDialog>

class QDate;

namespace Ui {
    class NewLeagueDialog;
}

class NewLeagueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewLeagueDialog(QWidget *parent = 0);
    ~NewLeagueDialog();

private slots:
    void on_pushButtonOkay_clicked();

    void on_pushButtonCancel_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonRemove_clicked();

    void on_dateEditFrom_dateChanged(QDate date);

    void on_dateEditTo_dateChanged(QDate date);

private:
    Ui::NewLeagueDialog *ui;
};

#endif // NEWLEAGUEDIALOG_H
