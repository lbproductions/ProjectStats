#ifndef GUI_DETAILS_LIVEGAMEDETAILS_DOKOLIVEGAMEDETAILS_DOKOLIVEGAMEROUNDTABLEITEM_H
#define GUI_DETAILS_LIVEGAMEDETAILS_DOKOLIVEGAMEDETAILS_DOKOLIVEGAMEROUNDTABLEITEM_H

#include <QTableWidgetItem>
#include <QObject>

namespace Database {
    class Player;
    class DokoRound;
    class Point;
}

namespace Gui {
namespace Details {
namespace LiveGameDetails {
namespace DokoLiveGameDetails {

class DokoLiveGameRoundTableItem : public QObject, public QTableWidgetItem
{
    Q_OBJECT
public:
    explicit DokoLiveGameRoundTableItem();

    virtual int points() = 0;

    virtual void setPoints(int points) = 0;
};

class DokoLiveGameRoundTablePlayerItem : public DokoLiveGameRoundTableItem
{
    Q_OBJECT
public:
    explicit DokoLiveGameRoundTablePlayerItem(Database::Player* player, Database::DokoRound* round);

    int points();

    void setPoints(int points);

private slots:
    void updateContent();

private:
    Database::Player* m_player;
    Database::DokoRound* m_round;
    Database::Point* m_point;
};

class DokoLiveGameRoundTableTotalPointsItem : public DokoLiveGameRoundTableItem
{
    Q_OBJECT
public:
    explicit DokoLiveGameRoundTableTotalPointsItem(Database::DokoRound* round);

    int points();

    void setPoints(int points);

private slots:
    void updateContent();

private:
    Database::DokoRound* m_round;
};

} // namespace DokoLiveGameDetails
} // namespace LiveGameDetails
} // namespace Details
} // namespace Gui

#endif // GUI_DETAILS_LIVEGAMEDETAILS_DOKOLIVEGAMEDETAILS_DOKOLIVEGAMEROUNDTABLEITEM_H
