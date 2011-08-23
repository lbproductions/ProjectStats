#ifndef SIDEBARITEMDELEGATE_H
#define SIDEBARITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPointer>

namespace Gui
{
namespace MainWindow
{

class SidebarTreeView;

class SidebarItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SidebarItemDelegate(SidebarTreeView *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
private:
    QPointer<SidebarTreeView> m_view;
};

}
}

#endif // SIDEBARITEMDELEGATE_H
