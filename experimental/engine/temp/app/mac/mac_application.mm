#import <Cocoa/Cocoa.h>

#include "temp/app/mac/mac_application.h"
#include "temp/core/thread_pool.h"

@interface ApplicationDelegate : NSObject < NSApplicationDelegate > {
}
@end

@implementation ApplicationDelegate
- (void)applicationWillFinishLaunching:(NSNotification *)notification {
    [[NSApp keyWindow] makeKeyAndOrderFront:NSApp];
    [[NSApp keyWindow] orderFrontRegardless];
}
@end

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
namespace app{
namespace mac {
    
struct MacApplication::Properties {
    NSApplication *app = nil;
    ApplicationDelegate *delegate = nil;
    core::ThreadPool::UPtr main_thread = core::ThreadPool::makeUnique("Main", 1);

    std::atomic_char exit_flag;
    std::function<void(void)> on_initialize = [](){};
    std::function<void(void)> on_update = [](){};
    std::function<void(void)> on_terminate = [](){};

    NSWindow *window_handle = nil;
};

MacApplication::MacApplication()
    : properties_(new Properties()) {
    properties_->app = [NSApplication sharedApplication];
    properties_->delegate = [[ApplicationDelegate alloc] init];
    [properties_->app setDelegate:properties_->delegate];
    [properties_->app setActivationPolicy:NSApplicationActivationPolicyRegular];

    properties_->exit_flag = 0;
}

MacApplication::~MacApplication() { [properties_->app terminate:properties_->app]; }

void MacApplication::setOnInitializeCallback(const std::function<void(void)> &on_initialize) {
    properties_->on_initialize = on_initialize;
}

void MacApplication::setOnUpdateCallback(const std::function<void(void)> &on_update) {
    properties_->on_update = on_update;
}

void MacApplication::setOnTerminateCallback(const std::function<void(void)> &on_terminate) {
    properties_->on_terminate = on_terminate;
}

temp::Int32 MacApplication::run() {
    auto delegate = [[WindowDelegate alloc] init];
    properties_->window_handle = [[NSWindow alloc]
        initWithContentRect:NSMakeRect(0, 0, 1080, 720)
                    styleMask:NSWindowStyleMaskTitled
                            | NSWindowStyleMaskMiniaturizable
                            | NSWindowStyleMaskClosable
                    backing:NSBackingStoreBuffered
                        defer:NO];
    [properties_->window_handle setTitle:@"てんぷら"];
    [properties_->window_handle center];
    [properties_->window_handle setDelegate:delegate];
    [properties_->window_handle makeKeyWindow];
    NSWindowCollectionBehavior behavior = [properties_->window_handle collectionBehavior];
    behavior |= NSWindowCollectionBehaviorManaged
                | NSWindowCollectionBehaviorParticipatesInCycle
                | NSWindowCollectionBehaviorFullScreenPrimary;
    [properties_->window_handle setCollectionBehavior:behavior];
    [properties_->window_handle orderFrontRegardless];

    properties_->on_initialize();

    auto future = properties_->main_thread->pushTask(0, [this](){mainLoop(); });
    [properties_->app run];
    properties_->exit_flag = 1;
    future.wait();

    properties_->on_terminate();

    return 0;
}

void MacApplication::exit() {
    properties_->exit_flag = 1;
    [properties_->app stop:properties_->app];
}

void* MacApplication::getNativeWindowHandle() {
    return properties_->window_handle;
}

void MacApplication::mainLoop() {
    while (!properties_->exit_flag) {
        properties_->on_update();
    }
}
    
}
}
}
