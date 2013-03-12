#include <QApplication>

#include <Misc/logger.h>
#include <Misc/cocoainitializer.h>
#include <Misc/handler.h>

int main(int argc, char *argv[])
{
    Logger::init();

#ifdef Q_WS_MAC
    CocoaInitializer cocoaInitializer;
    (void) cocoaInitializer; //supress unused variable warning
#endif

    Handler handler(argc, argv);

    if(handler.showMainWindow())
    {
        return handler.exec();
    }
    return 0;
}
