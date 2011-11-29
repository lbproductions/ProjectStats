#ifndef LEAGUEOVERVIEWWIDGET_H
#define LEAGUEOVERVIEWWIDGET_H

#include <QWidget>
#include <QPointer>

class QScrollArea;
class QFrame;

namespace Database
{
    class ChildCategorie;
    class Row;
    class LeagueFolderCategorie;
    class Game;
}

namespace Gui
{

namespace Details
{
    class DetailsWidget;
    class RowWidget;
}

namespace Misc
{
    class Splitter;
    class RowList;
    class Sheet;
}

namespace MainWindow
{
    class MainWindow;
namespace Views
{

namespace LeagueViewDetails{

class LeagueOverviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeagueOverviewWidget(Database::LeagueFolderCategorie *categorie, MainWindow *parent);


signals:
    void onPrevClicked();
    void onNextClicked();

public slots:
    void updateStatusbar();

private slots:
    void onGamesListRowsSelected(QList<Database::Row *> list);
    void onPlayersListRowsSelected(QList<Database::Row *> list);
    void on_rowList_selectionChanged();

private:
    void saveSettings();
    void restoreSettings();

    Misc::Splitter* m_basicSplitter;
    Misc::Splitter* m_viewSplitter;

    Misc::RowList* m_rowListPlayer;
    Misc::RowList* m_rowListGames;

    QScrollArea* m_scrollAreaDetails; //!< In dieser ScrollArea werden die DetailsWidgets angezeigt.
    Gui::Misc::Sheet* m_sheet;
    Details::DetailsWidget* m_rowWidget; //!< Speichert das aktuelle RowWidget

    QFrame* m_pastNextGame;

    Database::LeagueFolderCategorie* m_categorie;

};

}}}}

#endif // LEAGUEOVERVIEWWIDGET_H
