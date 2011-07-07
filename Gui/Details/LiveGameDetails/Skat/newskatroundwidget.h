#ifndef NEWSKATROUNDWIDGET_H
#define NEWSKATROUNDWIDGET_H

#include <QWidget>

#include <Database/Skat/skatlivegame.h>

namespace Ui {
    class NewSkatRoundWidget;
}

namespace Database
{
    class Player;
    namespace Skat
    {
        class SkatLiveGame;
    }
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

namespace SkatLiveGameDetails{

class NewSkatRoundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NewSkatRoundWidget(Database::Skat::SkatLiveGame* skatlivegame, QWidget *parent = 0);
    ~NewSkatRoundWidget();

    void calculatePoints();

    bool checkInputs();

private slots:
    void on_comboBoxGameType_currentIndexChanged(QString type);

    void on_comboBoxTrumpfFarbe_currentIndexChanged(QString color);

    void on_comboBoxWinner_currentIndexChanged(QString winner);

    void on_spinBoxMultiplikator_valueChanged(int );

    void on_pushButtonCreateRound_clicked();

private:
    Ui::NewSkatRoundWidget *ui;

    QPointer<Database::Skat::SkatLiveGame> m_skatlivegame;

signals:
    void roundCreated();
};

}}}}

#endif // NEWSKATROUNDWIDGET_H
