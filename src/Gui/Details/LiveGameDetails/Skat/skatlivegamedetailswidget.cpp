#include "skatlivegamedetailswidget.h"

#include <Database/Skat/skatlivegame.h>
#include <Gui/Details/LiveGameDetails/Skat/newskatroundwidget.h>
#include <Gui/Details/LiveGameDetails/Skat/skatlivegameroundtable.h>
#include <Database/player.h>
#include "handler.h"
#include "messagesystem.h"

#include <QFile>
#include <QDebug>

using namespace Gui::Details;

SkatLiveGameDetailsWidget::SkatLiveGameDetailsWidget(Database::Skat::SkatLiveGame* game, QWidget* parent) :
    LiveGameDetailsWidget(game,parent)
{
    m_skatlivegame = game;

    initializeItems();
    setupWidget();

    setFullscreenMode();
}

void SkatLiveGameDetailsWidget::initializeItems(){
    qDebug() << "Loading SkatLiveGameRoundTable...";
    m_roundTable = new LiveGameDetails::SkatLiveGameDetails::SkatLiveGameRoundTable(m_skatlivegame,this);
    LiveGameDetailsWidget::initializeItems();
}

void SkatLiveGameDetailsWidget::showRoundWidget(){
    m_skatRoundWidget = new LiveGameDetails::SkatLiveGameDetails::NewSkatRoundWidget(m_skatlivegame,this);

    QFile newround(":/stylesheet/newround_fullscreen");
    newround.open(QFile::ReadOnly);
    m_skatRoundWidget->setStyleSheet(newround.readAll());
    newround.close();

    m_newItemLayout->addWidget(m_skatRoundWidget);

    connect(m_skatRoundWidget,SIGNAL(roundCreated()),this,SLOT(onRoundCreated()));

    this->repaint();
}

void SkatLiveGameDetailsWidget::checkForEndOfGame(){
    if (m_skatlivegame->gameEnd() == "Rounds"){
        if (m_skatlivegame->rounds().size() > m_skatlivegame->maxRounds()){
            emit gameEnded();
            closeGame();
            timer->stop();
        }
    }
    if (m_skatlivegame->gameEnd() == "Points"){
        if (m_skatlivegame->maxPlayerPoints() > m_skatlivegame->maxPoints()){
            for (int i = 0; i<m_playerTotalPointsTable->columnCount();i++){
                foreach (Database::Player* p, m_skatlivegame->endGamePlayers()){
                   if (m_playerTotalPointsTable->horizontalHeaderItem(i)->text() == p->name()){
                       m_playerTotalPointsTable->horizontalHeaderItem(i)->setBackgroundColor(QColor("red"));
                       Handler::getInstance()->messageSystem()->showMessage(p->name()+" has ended game", p->name() + "has more than " + QString::number(m_skatlivegame->maxPoints()) + "and ended the game",p->avatarFilePath());
                       emit gameEnded();
                       closeGame();
                       timer->stop();
                    }
                 }
            }
        }
    }
}
