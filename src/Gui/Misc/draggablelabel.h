#ifndef DRAGGABLELABEL_H
#define DRAGGABLELABEL_H

#include <QLabel>

namespace Database {
    class PSRow;
}

class DraggableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DraggableLabel(Database::PSRow* row, QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *event);

signals:

public slots:

private:
    Database::PSRow* m_row;
};

#endif // DRAGGABLELABEL_H
