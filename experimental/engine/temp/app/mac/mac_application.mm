#import <Cocoa/Cocoa.h>
#include "temp/app/application.h"
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

class Application::Impl {
public:
    Impl()
        : app_(nil)
        , delegate_(nil)
        , main_thread_(core::ThreadPool::makeUnique("Main", 1))
        , on_initialize_([]() {})
        , on_update_([]() {})
        , on_terminate_([]() {}) {
        app_ = [NSApplication sharedApplication];
        delegate_ = [[ApplicationDelegate alloc] init];
        [app_ setDelegate:delegate_];
        [app_ setActivationPolicy:NSApplicationActivationPolicyRegular];

        exit_flag_ = 0;
    }

    ~Impl() { [app_ terminate:app_]; }

    void setOnInitializeCallback(const std::function<void(void)> &on_initialize) {
        on_initialize_ = on_initialize;
    }

    void setOnUpdateCallback(const std::function<void(void)> &on_update) {
        on_update_ = on_update;
    }

    void setOnTerminateCallback(const std::function<void(void)> &on_terminate) {
        on_terminate_ = on_terminate;
    }

    temp::Int32 run() {
        auto delegate = [[WindowDelegate alloc] init];
        window_handle_ = [[NSWindow alloc]
            initWithContentRect:NSMakeRect(0, 0, 1080, 720)
                      styleMask:NSWindowStyleMaskTitled
                                | NSWindowStyleMaskMiniaturizable
                                | NSWindowStyleMaskClosable
                        backing:NSBackingStoreBuffered
                          defer:NO];
        [window_handle_ setTitle:@"てんぷら"];
        [window_handle_ center];
        [window_handle_ setDelegate:delegate];
        [window_handle_ makeKeyWindow];
        NSWindowCollectionBehavior behavior = [window_handle_ collectionBehavior];
        behavior |= NSWindowCollectionBehaviorManaged
                    | NSWindowCollectionBehaviorParticipatesInCycle
                    | NSWindowCollectionBehaviorFullScreenPrimary;
        [window_handle_ setCollectionBehavior:behavior];
        [window_handle_ orderFrontRegardless];

        on_initialize_();

        auto future = main_thread_->pushTask(0, [this](){mainLoop(); });
        [app_ run];
        exit_flag_ = 1;
        future.wait();

        on_terminate_();

        return 0;
    }

    void exit() {
        exit_flag_ = 1;
        [app_ stop:app_];
    }

private:
    void mainLoop() {
        while (!exit_flag_) {
            on_update_();
        }
    }

    NSApplication *app_;
    ApplicationDelegate *delegate_;
    core::ThreadPool::UPtr main_thread_;

    std::atomic_char exit_flag_;
    std::function< void(void)> on_initialize_;
    std::function< void(void)> on_update_;
    std::function< void(void)> on_terminate_;

    NSWindow* window_handle_;
};

Application::Application() : impl_(new Impl) {}

Application::~Application() {}

void Application::setOnInitializeCallback(const std::function< void(void)> &on_initialize) {
    impl_->setOnInitializeCallback(on_initialize);
}

void Application::setOnUpdateCallback(const std::function< void(void)> &on_update) {
    impl_->setOnUpdateCallback(on_update);
}

void Application::setOnTerminateCallback(const std::function< void(void)> &on_terminate) {
    impl_->setOnTerminateCallback(on_terminate);
}

Int32 Application::run() { return impl_->run(); }

void Application::exit() { return impl_->exit(); }
    
}
}
