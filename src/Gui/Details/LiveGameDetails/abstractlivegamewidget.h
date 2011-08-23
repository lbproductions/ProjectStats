#ifndef ABSTRACTLIVEGAMEWIDGET_H
#define ABSTRACTLIVEGAMEWIDGET_H

#include <QWidget>

namespace Gui{

namespace Details{

namespace LiveGameDetails{

class AbstractLiveGameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractLiveGameWidget(QWidget *parent = 0);

signals:

public slots:

    virtual void setFullscreen();

    virtual void setNormalMode();

};

}}}

#endif // ABSTRACTLIVEGAMEWIDGET_H
