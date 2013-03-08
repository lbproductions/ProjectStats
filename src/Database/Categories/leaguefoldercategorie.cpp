#include "leaguefoldercategorie.h"

#include <Gui/MainWindow/Views/LeagueView/leagueview.h>

#include <Misc/handler.h>
#include <Database/database.h>
#include <Database/league.h>

#include <QDateTime>

#include <QIcon>

START_ROW_IMPLEMENTATION(LeagueFolderCategorie, Categorie, FolderCategorie)
{
    type->setValue(Categorie::FolderCategorieType);
    contentType->setValue(ChildCategorie::LeagueCategorieContentType);
    parentId->setValue(6);

    m_league = 0;
    m_gameModel = 0;
    m_playerModel = 0;
}

QString LeagueFolderCategorie::mimeType() const
{
    return "application/projectstats.leagueFolderCategorie";
}

QIcon LeagueFolderCategorie::icon() const
{
    if(ChildCategorie::icon->value().isNull())
    {
        return QIcon(":/graphics/icons/mac/sidebar/sidebar_folder_games");
    }

    return QIcon();
}


Gui::MainWindow::Views::View *LeagueFolderCategorie::view()
{

    if(m_view.isNull())
    {
        m_view = new Gui::MainWindow::Views::LeagueView(this);
        m_view->setWindowTitle(QString::fromUtf8("League \u2013 ")+name->value());
        m_view->setWindowIcon(icon());
    }

    return m_view;
}

Models::TableModel<Game,Games>* LeagueFolderCategorie::gamesModel(){
    if(m_gameModel == 0){
        if(m_league == 0){
            foreach(League* league, Leagues::instance()->allRows()) {
                if(league->categorieId->value() == this->id()) {
                    m_league = league;
                    break;
                }
            }
        }
       m_gameModel = new Models::TableModel<Game,Games>(m_league->games->value(),Games::instance());
    }
    return m_gameModel;
}

Models::TableModel<Player,Players>* LeagueFolderCategorie::playersModel(){
    if(m_playerModel == 0){
        if(m_league == 0){
            foreach(League* league, Leagues::instance()->allRows()) {
                if(league->categorieId->value() == this->id()) {
                    m_league = league;
                    break;
                }
            }
        }
       m_playerModel = new Models::TableModel<Player,Players>(m_league->players->value(),Players::instance());
    }
    return m_playerModel;
}

League* LeagueFolderCategorie::league() {
    if(m_league == 0) {
        foreach(League* league, Leagues::instance()->allRows()) {
            if(league->categorieId->value() == this->id()) {
                m_league = league;
                break;
            }
        }
    }
    return m_league;
}

END_ROW_IMPLEMENTATION()
