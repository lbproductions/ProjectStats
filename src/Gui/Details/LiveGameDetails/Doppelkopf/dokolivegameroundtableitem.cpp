#include "dokolivegameroundtableitem.h"

#include <Database/Doppelkopf/dokoround.h>
#include <Database/player.h>
#include <Database/point.h>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

DokoLiveGameRoundTableItem::DokoLiveGameRoundTableItem() :
    QTableWidgetItem()
{

}

DokoLiveGameRoundTablePlayerItem::DokoLiveGameRoundTablePlayerItem(Database::Player *player, Database::DokoRound *round) :
    DokoLiveGameRoundTableItem(),
    m_player(player),
    m_round(round),
    m_point(0)
{
    setFlags(flags() & ~Qt::ItemIsSelectable);

    setTextAlignment(Qt::AlignCenter);

    if(m_round->pointObjects->value().contains(m_player))
    {
        m_point = m_round->pointObjects->value(m_player);
    }

    if(!m_point)
    {
        setText("");
    }
    else
    {
        updateContent();
        connect(m_point->points,SIGNAL(changed()),this,SLOT(updateContent()));
    }
}

void DokoLiveGameRoundTablePlayerItem::updateContent()
{
    int points = m_point->points->value();
    QString text = QString::number(points);
    if(m_round->doko_soloPlayerId->value() > 0)
    {
        if (m_round->doko_re->value(m_player))
        {
            text += " (S";
            if(m_round->doko_hochzeitPlayerId->value() == m_player->id())
            {
                text += ",H)";
            }
            else if(m_round->doko_trumpfabgabePlayerId->value() == m_player->id())
            {
                text += ",T)";
            }
            else
            {
                text += ")";
            }
            setText(text);
        }
        else
        {
            setText(QString::number(points) + " (C)");
        }
    }
    else
    {
        if (m_round->doko_re->value(m_player))
        {
            text += " (R";
            if(m_round->doko_hochzeitPlayerId->value() == m_player->id())
            {
                text += ",H)";
            }
            else if(m_round->doko_trumpfabgabePlayerId->value() == m_player->id())
            {
                text += ",T)";
            }
            else
            {
                text += ")";
            }
            setText(text);
        }
        else
        {
            setText(QString::number(points) + " (C)");
        }
    }

    if (points < -9) {
        setBackgroundColor(QColor(255,0,0));
    }
    else if (points < -6) {
        setBackgroundColor(QColor(220,0,0));
    }
    else if (points < -3) {
        setBackgroundColor(QColor(188,0,0));
    }
    else if (points < 0) {
        setBackgroundColor(QColor(148,0,0));
    }
    else if (points > 9) {
        setBackgroundColor(QColor(24,255,0));
    }
    else if (points > 6) {
        setBackgroundColor(QColor(19,205,0));
    }
    else if (points > 3) {
        setBackgroundColor(QColor(13,141,0));
    }
    else if (points > 0) {
        setBackgroundColor(QColor(10,104,0));
    }
    else {
        setBackgroundColor("lightgray");
    }
}

int DokoLiveGameRoundTablePlayerItem::points()
{
    if(m_point)
    {
        return m_point->points->value();
    }

    return 0;
}

void DokoLiveGameRoundTablePlayerItem::setPoints(int points)
{
    if(!m_round->doko_re->value(m_player))
    {
        points = -points;
    }

    foreach(Database::Player* player, m_round->currentPlayingPlayers->value())
    {
        if(m_round->doko_re->value(player))
        {
            if(m_round->doko_soloPlayerId->value() == player->id())
            {
                m_round->pointObjects->value(player)->points->setValue(points*3);
            }
            else
            {
                m_round->pointObjects->value(player)->points->setValue(points);
            }
        }
        else
        {
            m_round->pointObjects->value(player)->points->setValue(-points);
        }
    }
}

DokoLiveGameRoundTableTotalPointsItem::DokoLiveGameRoundTableTotalPointsItem(Database::DokoRound *round) :
    DokoLiveGameRoundTableItem(),
    m_round(round)
{
    setFlags(flags() & ~Qt::ItemIsSelectable);

    setTextAlignment(Qt::AlignCenter);

    updateContent();
    connect(m_round->roundPoints,SIGNAL(changed()),this,SLOT(updateContent()));
    Database::Point* point = round->pointObjects->value(round->currentPlayingPlayers->value().at(0));
    connect(point->points,SIGNAL(changed()),this,SLOT(updateContent()));
}

void DokoLiveGameRoundTableTotalPointsItem::updateContent()
{
    Database::Player* player = m_round->currentPlayingPlayers->value().at(0);
    Database::Point* point = m_round->pointObjects->value(player);
    int points = qAbs(point->points->value());
    if(m_round->doko_soloPlayerId->value() == player->id())
    {
        points /= 3;
    }
    setText(QString::number(points));
}

int DokoLiveGameRoundTableTotalPointsItem::points()
{
    return text().toInt();
}

void DokoLiveGameRoundTableTotalPointsItem::setPoints(int points)
{
    foreach(Database::Player* player, m_round->currentPlayingPlayers->value())
    {
        if(m_round->doko_re->value(player))
        {
            if(m_round->doko_soloPlayerId->value() == player->id())
            {
                m_round->pointObjects->value(player)->points->setValue(points*3);
            }
            else
            {
                m_round->pointObjects->value(player)->points->setValue(points);
            }
        }
        else
        {
            m_round->pointObjects->value(player)->points->setValue(-points);
        }
    }
}
