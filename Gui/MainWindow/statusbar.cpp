#include "statusbar.h"

#include "mainwindow.h"
#include "statusbarbutton.h"

#include <QApplication>
#include <QDebug>
#include <QVBoxLayout>
#include <QAction>

using namespace Gui::MainWindow;

Statusbar::Statusbar(MainWindow *parent) :
    QFrame(parent)
{
    setStyleSheet("Gui--MainWindow--Statusbar {"
				"background-image: url(:/graphics/styles/mac/statusbar/background);"
				"background-repeat: repeat-x;"
				"background-position: top left;"
				"background-origin: margin;"
				"}");

    m_vBoxLayout = new QVBoxLayout(this);
    setLayout(m_vBoxLayout);

    setFixedHeight(23);
    m_vBoxLayout->setContentsMargins(10,8,0,0);
    //m_vBoxLayout->setSpacing(0);
}

void Statusbar::disableLeftButton()
{
    setLeftButton(QString(),0);
}

void Statusbar::setLeftButton(const QString &text, QAction *action)
{
    if(m_leftButton.isNull())
    {
	m_leftButton = new StatusbarButton(this);
	m_vBoxLayout->insertWidget(0,m_leftButton,0,Qt::AlignLeft);
	m_vBoxLayout->insertStretch(1,1);
    }

    m_leftButton->disconnect();

    if(text.isNull() || text.isEmpty() || action == 0)
    {
	m_leftButton->setVisible(false);
    }
    else
    {
	m_leftButton->setText(text);
	m_leftButton->setVisible(true);
	m_leftButton->setChecked(action->isChecked());
	m_leftButton->setCheckable(action->isCheckable());

	connect(m_leftButton,SIGNAL(toggled(bool)), action ,SLOT(toggle()));
    }
}
