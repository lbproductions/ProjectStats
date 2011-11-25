#include "sidebaritemdelegate.h"

#include "sidebartreeview.h"

#include <Database/categorie.h>
#include <Database/Categories/childcategorie.h>

#include <QPainter>
#include <QLineEdit>
#include <QDebug>
#include <QStandardItem>

using namespace Gui::MainWindow;

SidebarItemDelegate::SidebarItemDelegate(SidebarTreeView *parent) :
    QStyledItemDelegate(parent),
    m_view(parent)
{
}

void SidebarItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Database::Categorie *c = static_cast<Database::Categorie *>(index.data(Qt::UserRole + 1).value<void*>());
    if(c == 0)
    {
	return;
    }

    if(c->isParentCategorie())
    {
        QFont font = qVariantValue<QFont>(index.data(Qt::FontRole));
        font.setPixelSize(11);
        font.setBold(true);

        painter->setFont(font);
        painter->setPen(QColor(255,255,255,200));
        painter->drawText(option.rect.x(),option.rect.y()+16,
                  index.data().toString());

        painter->setPen(QColor(114,126,140,255));
        painter->drawText(option.rect.x(),option.rect.y()+15,
                  index.data().toString());
	return;
    }
    else
    {
        QStyledItemDelegate::paint(painter,option,index);

        QString text = index.data(Qt::UserRole + 2).toString();

        QFont font = qVariantValue<QFont>(index.data(Qt::FontRole));
        font.setPixelSize(12);

        if(m_view->selectionModel()->selectedIndexes().contains(index))
        {
            font.setBold(true);

            painter->setFont(font);
            painter->setPen(QColor(113,125,150,255));
            painter->drawText(option.rect.x()+30,option.rect.y()+18,
                      text);
            painter->setPen(QColor(255,255,255));
            painter->drawText(option.rect.x()+30,option.rect.y()+17,
                      text);
        }
        else
        {
            painter->setFont(font);
            painter->setPen(QColor(0,0,0,255));
            painter->drawText(option.rect.x()+30,option.rect.y()+17,
                      text);
        }

        return;
    }

    QStyledItemDelegate::paint(painter,option,index);
}

void Gui::MainWindow::SidebarItemDelegate::setModelData(QWidget *editor, QAbstractItemModel */*model*/, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);

    Database::ChildCategorie *categorie = static_cast<Database::ChildCategorie *>(index.data(Qt::UserRole + 1).value<void*>());

    QString text = lineEdit->text();
    categorie->name->setValue(text);

    categorie->standardItem()->setText(text);
}
