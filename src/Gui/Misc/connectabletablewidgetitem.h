#ifndef GUI_MISC_CONNECTABLETABLEWIDGETITEM_H
#define GUI_MISC_CONNECTABLETABLEWIDGETITEM_H

#include <QObject>
#include <QTableWidgetItem>

namespace Gui {
namespace Misc {

class ConnectableTableWidgetItem : public QObject, public QTableWidgetItem
{
    Q_OBJECT
public:
    ConnectableTableWidgetItem();

public slots:
    void setText(const QString &text);
};

} // namespace Misc
} // namespace Gui

#endif // GUI_MISC_CONNECTABLETABLEWIDGETITEM_H
