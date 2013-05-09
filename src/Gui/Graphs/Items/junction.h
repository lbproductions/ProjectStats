#ifndef GUI_GRAPHS_ITEMS_JUNCTION_H
#define GUI_GRAPHS_ITEMS_JUNCTION_H

#include <QList>

class QPainter;
class QPoint;

namespace Database{
    class Player;
}

namespace Gui {
namespace Graphs {
namespace Items {

class CoordinateSystem;

class Junction
{
public:
    Junction(QPoint p1, QPoint p2, CoordinateSystem* system);

    void draw(QPainter* painter);

    void draw(QPainter* painter, Database::Player *player);

    int x1();

    int x2();

    int y1();

    int y2();

private:
    int m_drawCount;

    CoordinateSystem* m_coordinateSystem;

    int m_x1;
    int m_x2;
    int m_y1;
    int m_y2;

    QList<Database::Player*> m_players;
};

} // namespace Items
} // namespace Graphs
} // namespace Gui

#endif // GUI_GRAPHS_ITEMS_JUNCTION_H
