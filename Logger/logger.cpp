#include "logger.h"

#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QTime>
#include <QDir>

Logger *Logger::m_instance = 0;

Logger::Logger() :
    QObject()
{
    m_logFile = new QFile(QDir::homePath()+"/Library/Logs/ProjectStats.log");

    if(!m_logFile->open(QIODevice::WriteOnly | QIODevice::Text))
    {
	print("Logfile konnte nicht geöffnet werden: " + m_logFile->fileName());
	print(m_logFile->errorString());
    }
}

Logger::Logger(const Logger &) :
    QObject()
{
}

Logger::~Logger()
{
    if(m_logFile != 0)
    {
	if(m_logFile->isOpen())
	{
	    m_logFile->close();
	}
	m_logFile->deleteLater();
	m_logFile = 0;
    }
}

Logger::SingletonGuard::~SingletonGuard()
{
    if(Logger::m_instance != 0)
    {
	Logger::m_instance->deleteLater();
	Logger::m_instance = 0;
    }
}

Logger *Logger::instance()
{
    static SingletonGuard guard;
    (void) guard;
    if(m_instance == 0)
    {
	m_instance = new Logger();
    }

    return m_instance;
}

void Logger::print(const QString &message)
{
    QString msg = QTime::currentTime().toString() + " " + message;

    fprintf(stderr, "%s\n", (char *)  msg.toAscii().data());

    if(m_logFile->isOpen())
    {
	QTextStream out(m_logFile);
	out << msg << endl;
    }
}

void Logger::debug(const char *msg)
{
    QString message = "[Debug]   | " + QString(msg);
    print(message);
}

void Logger::warning(const char *msg)
{
    QString message = "[Warning] | " + QString(msg);
    print(message);
}

void Logger::critical(const char *msg)
{
    QString message = "[Critical]| " + QString(msg);
    print(message);
}

void Logger::fatal(const char *msg)
{
    QString message = "[Fatal]   | " + QString(msg);
    print(message);
}

void Logger::init()
{
    qInstallMsgHandler(myMessageOutput);
}

void myMessageOutput(QtMsgType type, const char *msg)
{
    switch (type)
    {
    case QtDebugMsg:
	Logger::instance()->debug(msg);
	break;
    case QtWarningMsg:
	Logger::instance()->warning(msg);
	break;
    case QtCriticalMsg:
	Logger::instance()->critical(msg);
	break;
    case QtFatalMsg:
	Logger::instance()->fatal(msg);
	break;
    }
}
