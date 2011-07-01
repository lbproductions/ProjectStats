#ifndef SPLITTER_H
#define SPLITTER_H

#include <QSplitter>

namespace Gui
{

namespace Misc
{

#ifdef Q_WS_MAC
class MacSplitterHandle : public QSplitterHandle
{
Q_OBJECT
public:
    MacSplitterHandle(Qt::Orientation orientation, QSplitter *parent);
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;
};
#endif

class Splitter : public QSplitter
{
    Q_OBJECT
public:
    Splitter(Qt::Orientation orientation, QWidget *parent = 0);
#ifdef Q_WS_MAC
    QSplitterHandle *createHandle();
public slots:
    void myMoveSplitter(int pos);
#endif

};

}
}

#endif // SPLITTER_H
