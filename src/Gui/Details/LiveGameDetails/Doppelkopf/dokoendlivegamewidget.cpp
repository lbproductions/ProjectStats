#include "dokoendlivegamewidget.h"

#include <Database/Doppelkopf/dokolivegame.h>

#include <QGridLayout>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

DokoEndLiveGameWidget::DokoEndLiveGameWidget(Database::DokoLiveGame* livegame, QWidget* parent):
    EndLiveGameWidget(livegame,parent),
    m_dokolivegame(livegame)
{
    setupWidget();
}

void DokoEndLiveGameWidget::addTypeSpecificInformation(QGridLayout* layout, int row, int minColumn, Database::Player* player) {
    layout->addWidget(new QLabel(tr("Re"),this),0,minColumn);
    layout->addWidget(new QLabel(QString::number(m_dokolivegame->doko_re->value(player)),this),row,minColumn,Qt::AlignCenter);
    layout->addWidget(new QLabel(tr("ReWins"),this),0,minColumn+1);
    layout->addWidget(new QLabel(QString::number(m_dokolivegame->doko_reWins->value(player)),this),row,minColumn+1,Qt::AlignCenter);
    layout->addWidget(new QLabel(tr("Contra"),this),0,minColumn+2);
    layout->addWidget(new QLabel(QString::number(m_dokolivegame->doko_contra->value(player)),this),row,minColumn+2,Qt::AlignCenter);
    layout->addWidget(new QLabel(tr("ContraWins"),this),0,minColumn+3);
    layout->addWidget(new QLabel(QString::number(m_dokolivegame->doko_contraWins->value(player)),this),row,minColumn+3,Qt::AlignCenter);

}
