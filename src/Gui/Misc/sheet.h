#ifndef SHEET_H
#define SHEET_H

#include <QFrame>

namespace Gui
{
namespace Misc
{

class Sheet : public QFrame
{
    Q_OBJECT
public:
    explicit Sheet(QWidget *parent = 0);

    void setWidget(QWidget* widget);

private:
    QWidget* m_widget;
    
};

}
}
#endif // SHEET_H
