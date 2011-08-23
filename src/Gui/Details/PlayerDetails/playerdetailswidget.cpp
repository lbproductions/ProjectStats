#include "playerdetailswidget.h"
#include "ui_playerdetailswidget.h"

#include <Misc/handler.h>
#include <Database/database.h>
#include <Database/place.h>
#include <Misc/handler.h>
#include <Database/player.h>
#include <Gui/Misc/clickablelabel.h>
#include <Gui/Misc/placescombobox.h>

#include <QPixmap>
#include <QFileDialog>
#include <QColorDialog>

using namespace Gui::Details;

PlayerDetailsWidget::PlayerDetailsWidget(Database::Player *player, QWidget *parent) :
    DetailsWidget(player,parent),
    ui(new Ui::PlayerWidget),
    m_player(player)
{
    ui->setupUi(this);

    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

    m_labelAvatar = new Misc::ClickableLabel(this);
    ui->verticalLayoutAvatar->addWidget(m_labelAvatar);
    m_labelAvatar->setFixedSize(64,90);

    QPixmap pixmap(64,90);
    pixmap.load(":/graphics/images/player");
    m_labelAvatar->setPixmap(pixmap);
    m_labelAvatar->setScaledContents(true);
    m_labelAvatar->setFocusPolicy(Qt::ClickFocus);
    m_labelAvatar->setEnabled(true);

    ui->comboBoxGender->addItem("-");
    ui->comboBoxGender->addItem(tr("male"));
    ui->comboBoxGender->addItem(tr("female"));

    m_mayBeEditable = true;

    readPlayerData();
    connectToAttributes();
    setEditable(false);
    connect(player,SIGNAL(changed()),this,SLOT(readPlayerData()));

    connect(ui->lineEditName,SIGNAL(editingFinished()),this,SLOT(onLineEditNameEditingFinished()));
    connect(ui->pushButtonChooseColor,SIGNAL(clicked()),this,SLOT(onPushButtonChooseColorClicked()));
    connect(m_labelAvatar,SIGNAL(clicked()),this,SLOT(onAvatarClicked()));

    this->setTitle(tr("New Player"));
    this->setDescription(tr("Here you can create a new player"));
}

void PlayerDetailsWidget::readPlayerData()
{
    Q_ASSERT(!m_player.isNull());

    ui->spinBoxSize->setValue(m_player->size->value());
    ui->spinBoxWeight->setValue(m_player->weight->value());
    ui->comboBoxGender->setCurrentIndex(ui->comboBoxGender->findText(m_player->gender->value()));
    if (m_player->avatarPath->value() != ""){
        m_labelAvatar->setPixmap(m_player->avatarPath->value());
    }


    QGraphicsScene *s = new QGraphicsScene(ui->graphicsViewColor);
    s->addRect(0,0,15,15,QPen(Qt::SolidLine),QBrush(m_player->color->value()));
    ui->graphicsViewColor->setScene(s);
    ui->labelColorValue->setText(m_player->color->value().name());
}

void PlayerDetailsWidget::connectToAttributes()
{
    m_player->name->futureWatcher()->connectTo(ui->lineEditName);
    m_player->gender->futureWatcher()->connectTo(ui->labelGenderValue);
    m_player->size->futureWatcher()->connectTo(ui->labelSizeValue);
    m_player->weight->futureWatcher()->connectTo(ui->labelWeightValue);
}

PlayerDetailsWidget::~PlayerDetailsWidget()
{
    delete ui;
}

void PlayerDetailsWidget::setEditable(bool editable)
{
    m_editable = editable;

    ui->lineEditName->setReadOnly(!editable);
    ui->lineEditName->setFrame(editable);
    ui->pushButtonChooseColor->setVisible(editable);
    ui->labelSizeValue->setVisible(!editable);
    ui->spinBoxSize->setVisible(editable);
    ui->labelWeightValue->setVisible(!editable);
    ui->spinBoxWeight->setVisible(editable);
    ui->labelGenderValue->setVisible(!editable);
    ui->comboBoxGender->setVisible(editable);

    if (editable){
	while (ui->verticalLayoutResidence->count() > 0)
	{
	    ui->verticalLayoutResidence->itemAt(0)->widget()->setVisible(false);
	    ui->verticalLayoutResidence->removeItem(ui->verticalLayoutResidence->itemAt(0));
	}
        foreach(Database::Place* p, m_player->places->value()){
            Misc::PlacesComboBox* placesBox = new Misc::PlacesComboBox(this);
            placesBox->addItems(Database::Places::instance()->allRows());
	    placesBox->setCurrentPlace(p->id());
	    connect(placesBox,SIGNAL(currentIndexChanged(Database::Place*const,Database::Place*const)),this,
		    SLOT(onPlacesComboBoxCurrentIndexChanged(Database::Place*const,Database::Place*const)));
	    ui->verticalLayoutResidence->addWidget(placesBox);
	}
        if (m_player->places->value().size() == 0){
            Misc::PlacesComboBox* placesBox = new Misc::PlacesComboBox(this);
            placesBox->addItems(Database::Places::instance()->allRows());
	    connect(placesBox,SIGNAL(currentIndexChanged(Database::Place*const,Database::Place*const)),this,
		    SLOT(onPlacesComboBoxCurrentIndexChanged(Database::Place*const,Database::Place*const)));
	    ui->verticalLayoutResidence->addWidget(placesBox);
	}
    }
    else{
	while (ui->verticalLayoutResidence->count() > 0)
	{
	    ui->verticalLayoutResidence->itemAt(0)->widget()->setVisible(false);
	    ui->verticalLayoutResidence->removeItem(ui->verticalLayoutResidence->itemAt(0));
	}
        foreach(Database::Place* p, m_player->places->value()){
            ui->verticalLayoutResidence->addWidget(new QLabel(p->displayString->value()));
	}
    }

    //workaround fuer darstellungsfehler
    resize(size().width()+1,size().height()+1);
    resize(size().width()-1,size().height()-1);
}

void PlayerDetailsWidget::onPushButtonChooseColorClicked()
{
    Q_ASSERT(!m_player.isNull());
    if(m_colorDialog.isNull())
    {
	m_colorDialog = new QColorDialog(this);
	m_colorDialog->setAttribute(Qt::WA_DeleteOnClose);
    }
    m_colorDialog->setCurrentColor(m_player->color->value());
    connect(m_colorDialog,SIGNAL(colorSelected(const QColor &)),this,SLOT(colorSelected(const QColor &)));
    m_colorDialog->show();
}

void PlayerDetailsWidget::colorSelected(const QColor &color)
{
    Q_ASSERT(!m_player.isNull());
    m_player->color->setValue(color);
    readPlayerData();
}

void PlayerDetailsWidget::onLineEditNameEditingFinished()
{
    Q_ASSERT(!m_player.isNull());
    m_player->name->setValue(ui->lineEditName->text());
    readPlayerData();
}

void PlayerDetailsWidget::onPlacesComboBoxCurrentIndexChanged(Database::Place *const oldPlace , Database::Place *const newPlace)
{
    Q_ASSERT(!m_player.isNull());

    if (oldPlace != 0){
        //oldPlace->player->setValue(0);
    }
    if(newPlace != 0)
    {
        newPlace->playerId->setValue(m_player->id());
    }
    else
    {
	while (ui->verticalLayoutResidence->count() > 0)
	{
	    ui->verticalLayoutResidence->itemAt(0)->widget()->setVisible(false);
	    ui->verticalLayoutResidence->removeItem(ui->verticalLayoutResidence->itemAt(0));
	}
        foreach(Database::Place* p, m_player->places->value()){
            Misc::PlacesComboBox* placesBox = new Misc::PlacesComboBox(this);
            placesBox->addItems(Database::Places::instance()->allRows());
	    placesBox->setCurrentPlace(p->id());
	    connect(placesBox,SIGNAL(currentIndexChanged(Database::Place*const,Database::Place*const)),this,
		    SLOT(onPlacesComboBoxCurrentIndexChanged(Database::Place*const,Database::Place*const)));
	    ui->verticalLayoutResidence->addWidget(placesBox);
	}
    }
}

void PlayerDetailsWidget::on_spinBoxWeight_valueChanged(int weight)
{
    Q_ASSERT(!m_player.isNull());

    m_player->weight->setValue(weight);
    readPlayerData();
}

void PlayerDetailsWidget::on_spinBoxSize_valueChanged(int size)
{
    Q_ASSERT(!m_player.isNull());

    m_player->size->setValue(size);
    readPlayerData();
}

void PlayerDetailsWidget::on_comboBoxGender_currentIndexChanged(QString gender)
{
    Q_ASSERT(!m_player.isNull());

    if(gender != "-" && gender != ""){
        m_player->gender->setValue(gender);
	readPlayerData();
    }
}

void PlayerDetailsWidget::onAvatarClicked(){
    QString fileName = QFileDialog::getOpenFileName(0,
	 tr("Choose Avatar"), "~", tr("Database Files (*.png)"));
    if (fileName != ""){
	QPixmap pixmap(64,90);
	pixmap.load(fileName);
	m_labelAvatar->setPixmap(pixmap);
        m_player->avatarPath->setValue(fileName);
    }
}
