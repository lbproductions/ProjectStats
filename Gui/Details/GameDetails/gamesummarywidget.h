#ifndef DOKOLIVEGAMESUMMARYWIDGET_H
#define DOKOLIVEGAMESUMMARYWIDGET_H

#include <QWidget>
#include <QPointer>

#include <Gui/Details/summarywidget.h>

namespace Ui {
    class GameSummaryWidget;
}

namespace Database{
    class Game;
}

namespace Gui
{

namespace Details
{

    class GameDetailsWidget;

namespace GameDetails
{

class GameSummaryWidget : public SummaryWidget
{
    Q_OBJECT

public:
    explicit GameSummaryWidget(Database::Game* game, QWidget *parent = 0);
    ~GameSummaryWidget();

protected:
    Ui::GameSummaryWidget *ui;

    QPointer<Database::Game> m_game;


};

}}}

#endif // DOKOLIVEGAMESUMMARYWIDGET_H
