#ifndef ROWLISTHEADER_H
#define ROWLISTHEADER_H

#include <QHeaderView>

namespace Gui
{

namespace Misc
{

class RowListHeader : public QHeaderView
{
    Q_OBJECT
public:
    RowListHeader(Qt::Orientation orientation, QWidget * parent = 0 );

private slots:
    void hideHeader(bool hide);

protected:
    virtual void	 mousePressEvent(QMouseEvent* e);

private:
    QMenu *m_menu;
};

}
}
#endif // ROWLISTHEADER_H
