#include "commentsidebarpage.h"

#include <Database/livegame.h>

#include <QVBoxLayout>

using namespace Gui::Details::LiveGameDetails::Sidebar;

CommentSidebarPage::CommentSidebarPage(Database::LiveGame* liveGame, QWidget* parent):
    m_livegame(liveGame)
{
    this->setStyleSheet("QFrame{margin: 0px; padding: 0px; background: transparent; color: white; border: none; font-weight: bold;}");

    m_saveButton = new QPushButton(tr("Save"),this);
    m_title = new QLineEdit(this);
    m_comment = new QTextEdit(this);

    if(liveGame->comment->value() != ""){
        m_comment->setText(liveGame->comment->value());
    }

    if(liveGame->name->value() != ""){
        m_title->setText(liveGame->name->value());
    }

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_title);
    layout->addWidget(m_comment);
    layout->addWidget(m_saveButton);

    this->setLayout(layout);

    connect(m_saveButton,SIGNAL(clicked()),this,SLOT(saveButtonPressed()));
}

void CommentSidebarPage::saveButtonPressed(){
    m_livegame->name->setValue(m_title->text());
    m_livegame->comment->setValue(m_comment->toPlainText());
}
