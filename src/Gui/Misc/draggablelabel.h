#ifndef DRAGGABLELABEL_H
#define DRAGGABLELABEL_H

#include <QLabel>

#include <LBDatabase/LBDatabase.h>

class DraggableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DraggableLabel(Database::Row* row, QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *event);

signals:

public slots:

private:
    Database::Row* m_row;
};

#endif // DRAGGABLELABEL_H
