#ifndef CHOOSEDRINKCOUNTDIALOG_H
#define CHOOSEDRINKCOUNTDIALOG_H

#include <QDialog>

namespace Ui {
    class ChooseDrinkCountDialog;
}

class ChooseDrinkCountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseDrinkCountDialog(QWidget *parent = 0);
    ~ChooseDrinkCountDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void numberChosen(int number);

private:
    Ui::ChooseDrinkCountDialog *ui;
};

#endif // CHOOSEDRINKCOUNTDIALOG_H
