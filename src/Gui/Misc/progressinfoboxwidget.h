#ifndef PROGRESSINFOBOXWIDGET_H
#define PROGRESSINFOBOXWIDGET_H

#include <QWidget>
#include <QPointer>


namespace Gui
{

namespace Misc
{

class ValueLabel;
class PSProgressBar;

class ProgressInfoBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressInfoBoxWidget(QWidget *parent = 0);

    PSProgressBar* progressbar();

    void setLeftLabelText(QString text);

signals:

public slots:
    void setFullscreen();

    void setNormalMode();

private:

    ValueLabel* m_labelLeft;
    PSProgressBar* m_progressbar;

};

}}

#endif // PROGRESSINFOBOXWIDGET_H
