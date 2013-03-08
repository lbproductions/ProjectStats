#include "gamesummarywidget.h"
#include "ui_gamesummarywidget.h"

#include <Database/livegame.h>
#include <Database/player.h>
#include <Gui/Details/GameDetails/gamedetailswidget.h>

using namespace Gui::Details::GameDetails;

GameSummaryWidget::GameSummaryWidget(Database::Game* game, QWidget *parent) :
    SummaryWidget(game, parent),
    ui(new Ui::GameSummaryWidget),
    m_game(game),
    m_widget(new Gui::Details::GameDetailsWidget(m_game, this))
{
    ui->setupUi(this);
    ui->horizontalLayout->insertWidget(0, m_widget);

    mainSetup();
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

void GameSummaryWidget::mainSetup(){
    int size = m_game->playersSortedByPlacement->value().size();
    QLabel* position;
    QLabel* name;
    QFont font;
    QPixmap pixmap;

    for(int i = 0; i < size; i++) {
        position = new QLabel(this);
        position->setAlignment(Qt::AlignCenter);
        m_game->placement->mappingFutureWatcher(m_game->playersSortedByPlacement->value().at(i))->connectTo(position);
        m_labelList.append(position);

        name = new QLabel(this);
        name->setAlignment(Qt::AlignCenter);

        m_game->playersSortedByPlacement->value().at(i)->name->futureWatcher()->connectTo(name);
        font = name->font();

        font.setBold(true);
        font.setPointSize(10);
        name->setFont(font);
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
        ui->gridLayout->addWidget(position, i+1, 0);
        ui->gridLayout->addWidget(name, i+1, 1);
    }

    QLabel* nameHeader = new QLabel(tr("Name"));
    nameHeader->setAlignment(Qt::AlignCenter);
    font.setBold(false);
    font.setPointSize(9);
    nameHeader->setFont(font);
    m_labelList.append(nameHeader);
    ui->gridLayout->addWidget(nameHeader,0,1);
}

void GameSummaryWidget::update(){
    while(ui->gridLayout->count() > 0){
        QLayoutItem* i = ui->gridLayout->takeAt(0);
        if(i->widget()){
            delete i->widget();
        }
        delete i;
    }
    m_labelList.clear();

    mainSetup();
}
