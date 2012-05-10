#ifndef COMMENTSIDEBARPAGE_H
#define COMMENTSIDEBARPAGE_H

#include "sidebarpage.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

namespace Database{
    class LiveGame;
}

namespace Gui{

namespace Details{

namespace LiveGameDetails{

namespace Sidebar{

class CommentSidebarPage : public SidebarPage
{
public:
    CommentSidebarPage(Database::LiveGame* liveGame, QWidget* parent = 0);

private slots:
    void saveButtonPressed();

private:
    Database::LiveGame* m_livegame;

    QLineEdit* m_title;
    QTextEdit* m_comment;
    QPushButton* m_saveButton;
};

}}}}

#endif // COMMENTSIDEBARPAGE_H
