#ifndef NEWDOPPELKOPFROUNDWIDGET_H
#define NEWDOPPELKOPFROUNDWIDGET_H

#include <QDialog>
#include <QPointer>

namespace Database{
    class DokoRound;
    class DokoLiveGame;
    class Player;
}

namespace Gui
{

namespace Misc{
    class GroupBox;
    class CheckBox;
    class PlayerCheckBox;
}

namespace Details
{

namespace LiveGameDetails
{

namespace DokoLiveGameDetails{

class NewDoppelkopfRoundWidget : public QDialog
{
    Q_OBJECT

public:
    explicit NewDoppelkopfRoundWidget(Database::DokoLiveGame* game, QWidget *parent = 0);
    ~NewDoppelkopfRoundWidget();

public slots:
    void soloTypeChanged(Misc::CheckBox* check ,bool checked);
    void rePlayersChanged(Misc::CheckBox* check, bool checked);
    void hochzeitPlayerChanged(Misc::CheckBox* check, bool checked);

private:
    void setupWidget();

    void createSoloCheckBox();

    QPointer<Database::DokoLiveGame> m_dokoLiveGame;

    QPointer<Misc::GroupBox> m_soloGroupBox;
    QString m_soloType;
    QList<Misc::CheckBox*> m_soloCheckBoxes;

    QList<Misc::PlayerCheckBox*> m_reCheckBoxes;
    int m_reCount;

    QList<Misc::PlayerCheckBox*> m_hochzeitBoxes;

    QPointer<Database::Player> m_re1Player;
    QPointer<Database::Player> m_re2Player;
    QPointer<Database::Player> m_hochzeitPlayer;
    QPointer<Database::Player> m_trumpfabgabePlayer;
    QPointer<Database::Player> m_schweinereiPlayer;
    QPointer<Database::Player> m_soloPlayer;
};

}}}}

#endif // NEWDOPPELKOPFROUNDWIDGET_H
