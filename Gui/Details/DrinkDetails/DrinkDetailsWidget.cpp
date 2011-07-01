#include "drinkdetailswidget.h"
#include "ui_drinkdetailswidget.h"

#include <Gui/Misc/clickablelabel.h>
#include <Database/drink.h>
#include <Database/database.h>
#include <handler.h>

#include <QFileDialog>

using namespace Gui::Details;

DrinkDetailsWidget::DrinkDetailsWidget(Database::Drink* drink, QWidget *parent) :
    DetailsWidget(drink,parent),
    ui(new Ui::DrinkDetailsWidget),
    m_drink(drink)
{
    ui->setupUi(this);

    m_labelPicture = new Gui::Misc::ClickableLabel(this);
    ui->verticalLayoutPicture->addWidget(m_labelPicture);
    m_labelPicture->setFixedSize(50,150);

    QPixmap pixmap(50,150);
    pixmap.load(":/graphics/drinks/default");
    m_filePath = ":/graphics/drinks/default";
    m_labelPicture->setPixmap(pixmap);
    m_labelPicture->setScaledContents(true);
    m_labelPicture->setFocusPolicy(Qt::ClickFocus);
    m_labelPicture->setEnabled(true);

    if (m_drink->iconPath->value() == ""){
        m_drink->iconPath->setValue(m_filePath);
    }

    ui->comboBoxType->addItem(tr("Beer"));
    ui->comboBoxType->addItem(tr("Mixed beer"));
    ui->comboBoxType->addItem(tr("Wine"));
    ui->comboBoxType->addItem(tr("Schnapps"));

    connect(m_labelPicture,SIGNAL(clicked()),this,SLOT(onlabelPicclicked()));

    this->setTitle(tr("Create Drink"));
    this->setDescription(tr("This is the place to create a new drink to count them in a LiveGame"));

    readData();
    setEditable(false);

    m_mayBeEditable = true;
}

DrinkDetailsWidget::~DrinkDetailsWidget()
{
    delete ui;
}

void DrinkDetailsWidget::readData(){
    ui->comboBoxType->setCurrentIndex(ui->comboBoxType->findText(m_drink->type->value()));
    ui->doubleSpinBoxAlc->setValue(m_drink->alc->value());
    ui->doubleSpinBoxSize->setValue(m_drink->size->value());
    ui->lineEditName->setText(m_drink->name->value());

    ui->labelAlcoholValue->setText(QString::number(m_drink->alc->value()));
    ui->labelNameValue->setText(m_drink->name->value());
    ui->labelSizeValue->setText(QString::number(m_drink->size->value()));
    ui->labelTypeValue->setText(m_drink->type->value());

    m_filePath = m_drink->iconPath->value();

    QPixmap pixmap(50,150);
    pixmap.load(m_filePath);
    m_labelPicture->setPixmap(pixmap);
}

void DrinkDetailsWidget::onlabelPicclicked(){
    QString fileName = QFileDialog::getOpenFileName(0,
	 tr("Choose Drink-Picture"), "~", tr("Database Files (*.png)"));
    if (fileName != ""){
	QPixmap pixmap(50,150);
	pixmap.load(fileName);
	m_labelPicture->setPixmap(pixmap);
	m_filePath = fileName;
        m_drink->iconPath->setValue(m_filePath);
    }
}

void DrinkDetailsWidget::setEditable(bool editable)
{
    m_editable = editable;

    ui->comboBoxType->setVisible(editable);
    ui->doubleSpinBoxAlc->setVisible(editable);
    ui->doubleSpinBoxSize->setVisible(editable);
    ui->lineEditName->setVisible(editable);

    ui->labelAlcoholValue->setVisible(!editable);
    ui->labelNameValue->setVisible(!editable);
    ui->labelSizeValue->setVisible(!editable);
    ui->labelTypeValue->setVisible(!editable);

    //workaround fuer darstellungsfehler
    resize(size().width()+1,size().height()+1);
    resize(size().width()-1,size().height()-1);
}

void DrinkDetailsWidget::on_lineEditName_editingFinished()
{
    Q_ASSERT(!m_drink.isNull());
    m_drink->name->setValue(ui->lineEditName->text());
}

void DrinkDetailsWidget::on_comboBoxType_currentIndexChanged(QString )
{
    Q_ASSERT(!m_drink.isNull());
    if (ui->comboBoxType->currentText() != ""){
        m_drink->type->setValue(ui->comboBoxType->currentText());
    }
}

void DrinkDetailsWidget::on_doubleSpinBoxSize_editingFinished()
{
    Q_ASSERT(!m_drink.isNull());
    m_drink->size->setValue(ui->doubleSpinBoxSize->value());
}

void DrinkDetailsWidget::on_doubleSpinBoxAlc_editingFinished()
{
    Q_ASSERT(!m_drink.isNull());
    m_drink->alc->setValue(ui->doubleSpinBoxAlc->value());
}
