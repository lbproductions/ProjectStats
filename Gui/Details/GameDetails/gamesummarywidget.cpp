#include "gamesummarywidget.h"
#include "ui_gamesummarywidget.h"

#include <Database/livegame.h>
#include <Database/player.h>
#include <Gui/Details/GameDetails/gamedetailswidget.h>

#include <QGridLayout>
#include <QLabel>
#include <QDebug>

using namespace Gui::Details::GameDetails;

GameSummaryWidget::GameSummaryWidget(Database::Game* game, QWidget *parent) :
    SummaryWidget(parent),
    ui(new Ui::GameSummaryWidget)
{
    ui->setupUi(this);

    m_game = game;

    Gui::Details::GameDetailsWidget* widget = new Gui::Details::GameDetailsWidget(m_game,this);
    ui->verticalLayoutGameWidget->addWidget(widget);

    QGridLayout* layout = new QGridLayout();
    for(int i = 0; i<m_game->playersSortedByPlacement->value().size();i++){
        QLabel* position = new QLabel(this);
        position->setAlignment(Qt::AlignCenter);
        m_game->placement->mappingFutureWatcher()->connectTo(position,m_game->playersSortedByPlacement->value().at(i));
        QLabel* name = new QLabel(this);
        name->setAlignment(Qt::AlignCenter);
        m_game->playersSortedByPlacement->listFutureWatcher()->connectTo(name,m_game->playersSortedByPlacement->value().at(i));
        QFont font = name->font();
        font.setBold(true);
        font.setPointSize(14);
        QPixmap pixmap;
        switch(m_game->placement->value(m_game->playersSortedByPlacement->value().at(i))){
        case 1:
            pixmap.load(":/graphics/icons/general/medals/goldmedal");
            position->setPixmap(pixmap.scaled(50,50));
            name->setFont(font);
            break;
        case 2:
            pixmap.load(":/graphics/icons/general/medals/silvermedal");
            position->setPixmap(pixmap.scaled(50,50));
            name->setFont(font);
            break;
        case 3:
            pixmap.load(":/graphics/icons/general/medals/broncemedal");
            position->setPixmap(pixmap.scaled(50,50));
            name->setFont(font);
            break;
        default:
            break;
        }
        layout->addWidget(position,i,0);
        layout->addWidget(name,i,1);
    }
    ui->tab->setLayout(layout);
}

GameSummaryWidget::~GameSummaryWidget()
{
    delete ui;
}
