#include "dokolivegameroundtabledelegate.h"

#include "dokolivegameroundtable.h"
#include "dokolivegameroundtableitem.h"

#include <QLineEdit>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

DokoLiveGameRoundTableDelegate::DokoLiveGameRoundTableDelegate(DokoLiveGameRoundTable *parent) :
    QItemDelegate(parent),
    m_table(parent)
{
}

void DokoLiveGameRoundTableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);

    if(lineEdit)
    {
        lineEdit->setText(QString::number(m_table->itemAtIndex(index)->points()));
    }
}

void DokoLiveGameRoundTableDelegate::setModelData(QWidget *editor, QAbstractItemModel * /*model*/, const QModelIndex &index) const
{
    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);

    if(lineEdit)
    {
        m_table->itemAtIndex(index)->setPoints(lineEdit->text().toInt());
    }
}
