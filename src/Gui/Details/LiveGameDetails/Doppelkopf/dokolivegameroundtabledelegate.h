#ifndef GUI_DETAILS_LIVEGAMEDETAILS_DOKOLIVEGAMEDETAILS_DOKOLIVEGAMEROUNDTABLEDELEGATE_H
#define GUI_DETAILS_LIVEGAMEDETAILS_DOKOLIVEGAMEDETAILS_DOKOLIVEGAMEROUNDTABLEDELEGATE_H

#include <QItemDelegate>

namespace Gui {
namespace Details {
namespace LiveGameDetails {
namespace DokoLiveGameDetails {

class DokoLiveGameRoundTable;

class DokoLiveGameRoundTableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit DokoLiveGameRoundTableDelegate(DokoLiveGameRoundTable *parent = 0);

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private:
    DokoLiveGameRoundTable* m_table;
};

} // namespace DokoLiveGameDetails
} // namespace LiveGameDetails
} // namespace Details
} // namespace Gui

#endif // GUI_DETAILS_LIVEGAMEDETAILS_DOKOLIVEGAMEDETAILS_DOKOLIVEGAMEROUNDTABLEDELEGATE_H
