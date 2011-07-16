#ifndef CHOOSEDRINKCOUNTDIALOG_H
#define CHOOSEDRINKCOUNTDIALOG_H

#include <QDialog>

namespace Ui {
    class ChooseDrinkCountDialog;
}

namespace Database
{
    class Drink;
    class LiveGame;
    class Player;
}

class ChooseDrinkCountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseDrinkCountDialog(Database::Drink* drink, Database::Player* player, Database::LiveGame* game, QWidget *parent = 0);
    ~ChooseDrinkCountDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ChooseDrinkCountDialog *ui;

    Database::Drink* m_drink;

    Database::Player* m_player;

    Database::LiveGame* m_game;

};

#endif // CHOOSEDRINKCOUNTDIALOG_H
