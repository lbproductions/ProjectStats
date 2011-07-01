#ifndef HEADER_H
#define HEADER_H

#include <QWebView>

class QNetworkAccessManager;

namespace Gui
{

namespace Details
{

class GoogleMap : public QWebView 
{
	Q_OBJECT
public:
        GoogleMap(QWidget *parent=0);

public slots:
        void replyFinished(QNetworkReply*); 
        void loadCoordinates();
        void geoCode(QString);
        void clearCoordinates();
        void showCurrentLocation();

signals:
        void reloadMap();

private:
        QNetworkAccessManager *manager;
        QList<QPointF> coordinates;
        int pendingRequests;
};

}}

#endif 

