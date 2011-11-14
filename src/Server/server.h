#ifndef SERVER_H
#define SERVER_H

#include <QThread>
#include <vector>

class Server : public QThread
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    
    void run();
};

#endif // SERVER_H
