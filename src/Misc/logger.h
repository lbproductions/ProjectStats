#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class QFile;

class Logger : public QObject
{
    Q_OBJECT
public:
    ~Logger();

    static void init();

    static Logger *instance();

    void debug(const char *msg);
    void warning(const char *msg);
    void critical(const char *msg);
    void fatal(const char *msg);

protected:
    static Logger *m_instance;
    QFile *m_logFile;

    Logger();
    Logger(const Logger&);

    void print(const QString &message);

private:
    friend class SingletonGuard;
    class SingletonGuard
    {
    public:
	~SingletonGuard();
    };
};

void myMessageOutput(QtMsgType type, const char *msg);

#endif // LOGGER_H
