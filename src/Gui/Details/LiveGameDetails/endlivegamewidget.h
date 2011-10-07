#ifndef ENDLIVEGAMEWIDGET_H
#define ENDLIVEGAMEWIDGET_H

#include <QDialog>
#include <QPointer>

class QLineEdit;
class QTextEdit;
class QGridLayout;

namespace Database
{
    class LiveGame;
    class Player;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

/**
* Widget, das ein LiveGame beendet. Dabei wird der Name und der Kommentar des LiveGames eingegeben. Erbt eine Klasse von dieser, so muss
  im Konstruktor setupWidget() ausgeführt werden, damit das Widget korrekt dargestellt wird.
*/
class EndLiveGameWidget : public QDialog
{
    Q_OBJECT

public:
    /**
    * Erstellt eine neue Instanz des EndLiveGameWidget für das übergebene LiveGame.
    */
    explicit EndLiveGameWidget(Database::LiveGame* livegame, QWidget *parent = 0);

    ~EndLiveGameWidget();

    virtual void addTypeSpecificInformation(QGridLayout* layout, int row, int minColumn, Database::Player* player);

private slots:
    /**
    * Beendet das Spiel endgültig. Der eingebene Name und Kommentar werden für das Spiel gesetzt.
    */
    void on_pushButtonFinish_clicked();

    void on_pushButtonCancel_clicked();

protected:
    QPointer<Database::LiveGame> m_livegame;

    QLineEdit* m_nameLineEdit;
    QTextEdit* m_commentTextEdit;

    void setupWidget();

};

}
}
}

#endif // ENDLIVEGAMEWIDGET_H
