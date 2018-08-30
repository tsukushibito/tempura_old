#import <Cocoa/Cocoa.h>

#include "temp/system/mac/mac_application.h"

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
namespace system {
namespace mac {
    
struct MacApplication::Properties {
    NSApplication *app = nil;
    ApplicationDelegate *delegate = nil;
    TaskManager::UPtr main_thread = TaskManager::MakeUnique("Main", 1);
    // TaskManager::UPtr main_thread = TaskManager::AllocateUnique(std::allocator<int>(), "Main", 1);

    std::atomic_char exit_flag;

    NSWindow *window_handle = nil;
};

MacApplication::MacApplication()
    : properties_(new Properties()) {
    properties_->app = [NSApplication sharedApplication];
    properties_->delegate = [[ApplicationDelegate alloc] init];
    [properties_->app setDelegate:properties_->delegate];
    [properties_->app setActivationPolicy:NSApplicationActivationPolicyRegular];

    properties_->exit_flag = 0;

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

    native_window_handle_ = properties_->window_handle;
}

MacApplication::~MacApplication() { [properties_->app terminate:properties_->app]; }

temp::Int32 MacApplication::Run() {
    on_initialize()();

    auto future = properties_->main_thread->PushTask([this](){ MainLoop(); });
    [properties_->app run];
    properties_->exit_flag = 1;
    future.wait();

    on_terminate()();

    return 0;
}

void MacApplication::Exit() {
    properties_->exit_flag = 1;
    [properties_->app stop:properties_->app];
}


void MacApplication::MainLoop() {
    while (!properties_->exit_flag) {
        on_update()();
    }
}
    
}
}
}
