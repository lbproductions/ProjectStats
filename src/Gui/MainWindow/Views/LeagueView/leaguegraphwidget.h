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
    QTreeWidget* m_treeWidget;
    Gui::Misc::Splitter* m_splitter;

    QScrollArea* m_scrollAreaDetails;
    Gui::Graphs::GraphView* m_graphview;

    Database::LeagueFolderCategorie* m_categorie;


};

}}}}

#endif // LEAGUEGRAPHWIDGET_H
