#ifndef LEAGUEGRAPHWIDGET_H
#define LEAGUEGRAPHWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QPointer>

class QScrollArea;

namespace Database{
    class LeagueFolderCategorie;
}

namespace Gui
{

namespace Misc{
    class Splitter;
}

namespace Graphs
{
    class GraphView;
}

namespace MainWindow
{
namespace Views
{

namespace LeagueViewDetails{

class LeagueGraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeagueGraphWidget(Database::LeagueFolderCategorie *categorie, QWidget *parent = 0);

signals:

public slots:
    void graphClicked(QTreeWidgetItem* item);

private:
    QPointer<QTreeWidget> m_treeWidget;
    QPointer<Gui::Misc::Splitter> m_splitter;

    QPointer<QScrollArea> m_scrollAreaDetails;
    QPointer<Gui::Graphs::GraphView> m_graphview;

    QPointer<Database::LeagueFolderCategorie> m_categorie;


};

}}}}

#endif // LEAGUEGRAPHWIDGET_H
