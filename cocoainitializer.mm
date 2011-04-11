#include "cocoainitializer.h"

#include <AppKit/AppKit.h>
#include <Cocoa/Cocoa.h>
#include <AppKit/NSApplication.h>
#include <Sparkle/Sparkle.h>
#import <objc/objc-runtime.h>

#include <QApplication>

void terminate(id /*sender*/)
{
     qApp->quit();
}

class CocoaInitializer::Private
{
    public:
	NSAutoreleasePool* autoReleasePool;
};

CocoaInitializer::CocoaInitializer()
{
    d = new CocoaInitializer::Private();
    NSApplicationLoad();
    d->autoReleasePool = [[NSAutoreleasePool alloc] init];
    Method m = class_getInstanceMethod([NSApplication class], @selector(terminate) );
    method_setImplementation( m, (IMP) terminate );
}

CocoaInitializer::~CocoaInitializer()
{
    [d->autoReleasePool release];
    delete d;
}
