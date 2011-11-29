#include "placedetailswidget.h"
#include "ui_placedetailswidget.h"

#include <Misc/handler.h>
#include <Database/database.h>
#include <Database/player.h>
#include <Database/place.h>
#include <Gui/Misc/clickablelabel.h>
#include <Gui/Details/PlaceDetails/googlemap.h>

#include <QDialog>
#include <QFileDialog>

using namespace Gui::Details;

PlaceDetailsWidget::PlaceDetailsWidget(Database::Place* place, QWidget *parent) :
    DetailsWidget(place,parent),
    ui(new Ui::PlaceDetailsWidget),
    m_place(place)
{
    ui->setupUi(this);

    ui->lineEditTown->setFocus();

    ui->comboBoxPlayer->addItem("");
    foreach(Database::Player* p, Database::Players::instance()->allRows()){
	if(p != 0)
	{
            ui->comboBoxPlayer->addItem(p->name->value());
	}
    }

    m_labelPicture = new Misc::ClickableLabel(this);
    ui->verticalLayoutPicture->insertWidget(0,m_labelPicture);
    m_labelPicture->setFixedSize(30,30);

    QPixmap pixmap(30,30);
    pixmap.load(":/graphics/places/wappen_default");
    m_filePath = ":/graphics/places/wappen_default";
    m_labelPicture->setPixmap(pixmap);
    m_labelPicture->setScaledContents(true);
    m_labelPicture->setFocusPolicy(Qt::ClickFocus);
    m_labelPicture->setEnabled(true);

    if (m_place->iconPath->value() == ""){
        m_place->iconPath->setValue(m_filePath);
    }

    connect(m_labelPicture,SIGNAL(clicked()),this,SLOT(onlabelPicclicked()));

    m_map = new GoogleMap(this);
    m_map->setGeometry(QRect(150, 20, 341, 271));
    m_map->setMaximumSize(341,271);
    m_map->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    m_map->load(QUrl("qrc:/html/index.html") ) ;
    ui->verticalLayoutMap->insertWidget(0,m_map);

    ui->textEditComment->setAttribute(Qt::WA_MacShowFocusRect,true);

    this->setTitle(tr("Create Place"));
    this->setDescription(tr("Possibility to create a new place, e.g. for being a site for a game"));

    ui->lineEditPLZ->setFocus();

    readPlaceData();
    connectToAttributes();
    setEditable(false);

    m_mayBeEditable = true;

    m_map->clearCoordinates();
    m_map->geoCode(m_place->displayString->value());
}

PlaceDetailsWidget::~PlaceDetailsWidget()
{
    delete ui;
}

void PlaceDetailsWidget::readPlaceData(){
    ui->textEditComment->setText(m_place->comment->value());
    /*
    if(m_place->player->value() != 0){
        ui->comboBoxPlayer->setCurrentIndex(ui->comboBoxPlayer->findText(m_place->player->value()->name->value()));
    }
    */

    m_filePath = m_place->iconPath->value();

    QPixmap pixmap(30,30);
    pixmap.load(m_filePath);
    m_labelPicture->setPixmap(pixmap);

    m_map->clearCoordinates();
    m_map->geoCode(m_place->displayString->value());
}

void PlaceDetailsWidget::connectToAttributes(){
    m_place->comment->futureWatcher()->connectTo(ui->labelCommentValue);
    m_place->players->futureWatcher()->connectTo(ui->labelHomeOfValue);
    m_place->nummer->futureWatcher()->connectTo(ui->labelNrValue);
    m_place->plz->futureWatcher()->connectTo(ui->labelPLZValue);
    m_place->strasse->futureWatcher()->connectTo(ui->labelStreetValue);
    m_place->ort->futureWatcher()->connectTo(ui->labelTownValue);

    m_place->nummer->futureWatcher()->connectTo(ui->lineEditNumber);
    m_place->plz->futureWatcher()->connectTo(ui->lineEditPLZ);
    m_place->strasse->futureWatcher()->connectTo(ui->lineEditStreet);
    m_place->ort->futureWatcher()->connectTo(ui->lineEditTown);
}

void PlaceDetailsWidget::setEditable(bool editable){
    ui->labelCommentValue->setVisible(!editable);
    ui->labelHomeOfValue->setVisible(!editable);
    ui->labelNrValue->setVisible(!editable);
    ui->labelPLZValue->setVisible(!editable);
    ui->labelStreetValue->setVisible(!editable);
    ui->labelTownValue->setVisible(!editable);
    m_map->setVisible(!editable);
    ui->labelMap->setVisible(!editable);

    ui->lineEditNumber->setVisible(editable);
    ui->lineEditPLZ->setVisible(editable);
    ui->lineEditStreet->setVisible(editable);
    ui->lineEditTown->setVisible(editable);
    ui->textEditComment->setVisible(editable);
    ui->comboBoxPlayer->setVisible(editable);

    //workaround fuer darstellungsfehler
    resize(size().width()+1,size().height()+1);
    resize(size().width()-1,size().height()-1);
}

void PlaceDetailsWidget::on_lineEditPLZ_editingFinished()
{
    m_place->plz->setValue(ui->lineEditPLZ->text().toInt());
    readPlaceData();
}

void PlaceDetailsWidget::on_lineEditTown_editingFinished()
{
    m_place->ort->setValue(ui->lineEditTown->text());
    readPlaceData();
}

void PlaceDetailsWidget::on_lineEditStreet_editingFinished()
{
    m_place->strasse->setValue(ui->lineEditStreet->text());
    readPlaceData();
}

void PlaceDetailsWidget::on_lineEditNumber_editingFinished()
{
    m_place->nummer->setValue(ui->lineEditNumber->text().toInt());
    readPlaceData();
}

void PlaceDetailsWidget::on_textEditComment_textChanged()
{
    m_place->comment->setValue(ui->textEditComment->toPlainText());
}

void PlaceDetailsWidget::on_comboBoxPlayer_currentIndexChanged(QString /*name*/)
{
    /*
    Q_ASSERT(!m_place.isNull());
    if (ui->comboBoxPlayer->currentText() != ""){
        Database::Player* currentPlayer
        QList<Database::Player*> list = Database::Players::instance()->rowsBySqlCondition("WHERE name = " + ui->comboBoxPlayer->currentText());
        if(list.size() > 0){
            m_place->playerId->setValue(list.first()->id());
        }
    }
    */
}

void PlaceDetailsWidget::onlabelPicclicked(){
    QString fileName = QFileDialog::getOpenFileName(0,
         tr("Choose Place-Picture"), QDir::homePath() , tr("Picture Files (*.png)"));
    if (fileName != ""){
	QPixmap pixmap(50,150);
	pixmap.load(fileName);
	m_labelPicture->setPixmap(pixmap);
	m_filePath = fileName;
        m_place->iconPath->setValue(m_filePath);
    }
}

void Gui::Details::PlaceDetailsWidget::on_pushButtonReload_clicked()
{
    m_map->clearCoordinates();
    m_map->geoCode(m_place->displayString->value());
}
