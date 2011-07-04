#import "macwindowcontroller.h"

#ifdef Q_WS_MAC

#include <Cocoa/Cocoa.h>

@interface MacWindowController : NSObject {
    QWidget *m_widget;
}

- (void)setUpOSFullScreenButton:(QWidget*)mainWindow;
- (IBAction)enterFullScreen: sender;

@end  // @interface BrowserWindowController(Private)

@implementation MacWindowController

- (void)setUpOSFullScreenButton:(QWidget*)widget
{
    m_widget = widget;
    NSView *view = (NSView*) m_widget->winId();
    NSWindow* window = [view window];

    if ([window respondsToSelector:@selector(toggleFullScreen:)]) {
        NSWindowCollectionBehavior behavior = [window collectionBehavior];
        behavior |= NSWindowCollectionBehaviorFullScreenPrimary;
        [window setCollectionBehavior:behavior];

        NSButton* fullscreenButton = [window standardWindowButton:NSWindowFullScreenButton];
        [fullscreenButton setAction:@selector(enterFullScreen:)];
        [fullscreenButton setTarget:self];
    }
}

- (IBAction)enterFullScreen: sender
{
    (void) sender; //supress unused parameter error
    NSView *view = (NSView*) m_widget->winId();
    NSWindow* window = [view window];
//    [view enterFullScreenMode: view.window.screen
//                  withOptions: nil];
     [window toggleFullScreen: nil];
}

@end

void setUpFullScreenButton(QWidget *window)
{
    MacWindowController* controller = [[MacWindowController alloc] init];
    [controller setUpOSFullScreenButton:window];
}
#endif
