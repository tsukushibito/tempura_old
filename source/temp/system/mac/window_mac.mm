/**
* @file window.mm
* @brief window class
* @author tsukushibito
* @version 0.0.1
* @date 2016-02-21
*/
#import <Cocoa/Cocoa.h>
#include "temp/system/window.h"
#include "temp/system/application.h"

@interface WindowDelegate : NSObject < NSWindowDelegate > {
}
- (void)windowWillClose:(NSNotification *)notification;
@end

@implementation WindowDelegate
- (void)windowWillClose:(NSNotification *)notification {
    // NSLog(@"windowWillClose");
    // temp::system::Application::getInstance().exit();
    [NSApp stop:(NSApp)];
}
@end

namespace temp {
namespace system {

class Window::Impl {
public:
    Impl(Size width, Size height) {
        delegate_ = [[WindowDelegate alloc] init];
        window_ = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, width, height)
                                              styleMask:NSTitledWindowMask | NSMiniaturizableWindowMask | NSClosableWindowMask
                                                backing:NSBackingStoreBuffered
                                                  defer:NO];
        [window_ setTitle:@"てんぷら"];
        [window_ center];
        [window_ setDelegate:delegate_];
        [window_ makeKeyWindow];
        NSWindowCollectionBehavior behavior = [window_ collectionBehavior];
        behavior |= NSWindowCollectionBehaviorManaged | NSWindowCollectionBehaviorParticipatesInCycle |
                    NSWindowCollectionBehaviorFullScreenPrimary;
        [window_ setCollectionBehavior:behavior];
        [window_ orderFrontRegardless];
    }

    ~Impl() {}

    WindowHandle getWindowHandle() const {
        WindowHandle handle;
        handle.pointer_ = (__bridge void *)window_;
        return handle;
    }

private:
    NSWindow *window_;
    WindowDelegate *delegate_;
};

Window::Window(Size width, Size height) : impl_(new Impl(width, height)) {}

Window::~Window() {}

WindowHandle Window::getWindowHandle() const { return impl_->getWindowHandle(); }

Window::SPtr Window::create(Size width, Size height) {
    struct Creator : public Window {
        Creator(Size width, Size height) : Window(width, height) {}
    };

    auto p = std::make_shared< Creator >(width, height);
    return std::move(p);
}
}
}
