#ifndef SPLITTER_H
#define SPLITTER_H

#include <QSplitter>

namespace Gui
{

namespace Misc
{

#ifdef Q_WS_MAC

class Splitter;

class MacSplitterHandle : public QSplitterHandle
{
Q_OBJECT
public:
    MacSplitterHandle(Qt::Orientation orientation, Splitter *parent);
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;
};
#endif

class Splitter : public QSplitter
{
    Q_OBJECT
public:
    Splitter(Qt::Orientation orientation, QWidget *parent = 0);

    void setFullscreen(bool fullscreen);

    bool isFullscreen();

    void setLeftToRight(bool leftToRight);

    bool isLeftToRight();

#ifdef Q_WS_MAC
    QSplitterHandle *createHandle();
public slots:
    void myMoveSplitter(int pos);
#endif

private:
    bool m_fullscreen;
    bool m_leftToRight;
};

}
}

#endif // SPLITTER_H
