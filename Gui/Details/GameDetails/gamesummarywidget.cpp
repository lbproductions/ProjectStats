#include "gamesummarywidget.h"
#include "ui_gamesummarywidget.h"

#include <Database/livegame.h>
#include <Database/player.h>
#include <Gui/Details/GameDetails/gamedetailswidget.h>

using namespace Gui::Details::GameDetails;

GameSummaryWidget::GameSummaryWidget(Database::Game* game, QWidget *parent) :
    SummaryWidget(parent),
    ui(new Ui::GameSummaryWidget),
    m_game(game),
    m_widget(new Gui::Details::GameDetailsWidget(m_game, this))
{
    ui->setupUi(this);
    ui->horizontalLayout->insertWidget(0, m_widget);

    int size = m_game->playersSortedByPlacement->value().size();
    QLabel* position;
    QLabel* name;
    QFont font;
    QPixmap pixmap;

    for(int i = 0; i < size; i++) {
        position = new QLabel(this);
        position->setAlignment(Qt::AlignCenter);
        m_game->placement->mappingFutureWatcher()->connectTo(position, m_game->playersSortedByPlacement->value().at(i));
        m_labelList.append(position);

        name = new QLabel(this);
        name->setAlignment(Qt::AlignCenter);
        m_game->playersSortedByPlacement->listFutureWatcher()->connectTo(name,m_game->playersSortedByPlacement->value().at(i));
        font = name->font();
        font.setBold(true);
        m_labelList.append(name);

        switch(m_game->placement->value(m_game->playersSortedByPlacement->value().at(i)))
        {
            case 1:
                pixmap.load(":/graphics/icons/general/medals/goldmedal-scaled");
                position->setPixmap(pixmap);
                font.setPointSize(24);
                name->setFont(font);
                break;

            case 2:
                pixmap.load(":/graphics/icons/general/medals/silvermedal-scaled");
                position->setPixmap(pixmap);
                font.setPointSize(16);
                name->setFont(font);
                break;

            case 3:
                pixmap.load(":/graphics/icons/general/medals/broncemedal-scaled");
                position->setPixmap(pixmap);
                font.setPointSize(10);
                name->setFont(font);
                break;

            default:
                break;

        }

        ui->gridLayout->addWidget(position, i, 0);
        ui->gridLayout->addWidget(name, i, 1);
    }
}

GameSummaryWidget::~GameSummaryWidget()
{
    QListIterator<QLabel *> it(m_labelList);

    while (it.hasNext())
    {
        delete it.next();
    }

    delete m_widget;
    delete ui;
}
