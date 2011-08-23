#ifndef PSPROGRESSBAR_H
#define PSPROGRESSBAR_H

#include <QProgressBar>
#include <QPair>
#include <QHash>

#include <Gui/Misc/valuelabel.h>

namespace Gui
{

namespace Misc
{

class PSProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit PSProgressBar(QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);

    void registerNewDisplayValue(QString hashString, int value, QString displayText);

    void mousePressEvent(QMouseEvent *event);

signals:

public slots:
    void setFullscreen();

    void setNormalMode();

private:
    QString m_text;

    int m_clickcount;
    QHash<QString,QPair<int,ValueLabel*> > m_values;

};
}}

#endif // PSPROGRESSBAR_H
