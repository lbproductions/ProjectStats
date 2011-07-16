#ifndef MACWINDOWCONTROLLER_H
#define MACWINDOWCONTROLLER_H

#include <QWidget>

#ifdef Q_WS_MAC

void setUpFullScreenButton(QWidget *window);

void toggleFullscreen(QWidget* widget);

#endif // Q_WS_MAC

#endif // MACWINDOWCONTROLLER_H
