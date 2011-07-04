#ifndef MACWINDOWCONTROLLER_H
#define MACWINDOWCONTROLLER_H

#include <QWidget>

#ifdef Q_WS_MAC

#include <Cocoa/Cocoa.h>

void setUpFullScreenButton(QWidget *window);

#endif // Q_WS_MAC

#endif // MACWINDOWCONTROLLER_H
