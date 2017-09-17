/**
* @file window.mm
* @brief window class
* @author tsukushibito
* @version 0.0.1
* @date 2016-02-21
*/
#import <Cocoa/Cocoa.h>
#include "temp/system/application.h"
#include "temp/system/mac/mac.h"
#include "temp/system/window.h"
#include "temp/temp_assert.h"

@interface WindowDelegate : NSObject<NSWindowDelegate> {
}
- (void)windowWillClose:(NSNotification*)notification;
@end

@implementation WindowDelegate
- (void)windowWillClose:(NSNotification*)notification {
    // NSLog(@"windowWillClose");
    // temp::system::Application::instance().exit();
    [NSApp stop:(NSApp)];
}
@end

namespace temp {
namespace system {

class Window::Impl {
public:
    Impl(Size width, Size height) {
        delegate_ = [[WindowDelegate alloc] init];
        window_   = [[NSWindow alloc]
            initWithContentRect:NSMakeRect(0, 0, width, height)
                      styleMask:NSWindowStyleMaskTitled
                                | NSWindowStyleMaskMiniaturizable
                                | NSWindowStyleMaskClosable
                        backing:NSBackingStoreBuffered
                          defer:NO];
        [window_ setTitle:@"てんぷら"];
        [window_ center];
        [window_ setDelegate:delegate_];
        [window_ makeKeyWindow];
        NSWindowCollectionBehavior behavior = [window_ collectionBehavior];
        behavior |= NSWindowCollectionBehaviorManaged
                    | NSWindowCollectionBehaviorParticipatesInCycle
                    | NSWindowCollectionBehaviorFullScreenPrimary;
        [window_ setCollectionBehavior:behavior];
        [window_ orderFrontRegardless];
    }

    ~Impl() {}

    void* nativeHandle() const { return window_; }

private:
    NSWindow*       window_;
    WindowDelegate* delegate_;
};

Window::Window(Size width, Size height)
    : impl_(new Impl(width, height)), width_(width), height_(height) {}

Window::~Window() {}

Window::NativeHandle Window::nativeHandle() const {
    return impl_->nativeHandle();
}
}
}
