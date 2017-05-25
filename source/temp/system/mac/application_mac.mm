/**
 * @file application.mm
 * @brief mac application class
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-21
 */
#import <Cocoa/Cocoa.h>
#include <thread>
#include "temp/system/application.h"
#include "temp/system/thread_pool.h"

@interface ApplicationDelegate : NSObject < NSApplicationDelegate > {
}
@end

@implementation ApplicationDelegate
- (void)applicationWillFinishLaunching:(NSNotification *)notification {
    [[NSApp keyWindow] makeKeyAndOrderFront:NSApp];
    [[NSApp keyWindow] orderFrontRegardless];
}
@end

namespace temp {
namespace system {

class Application::Impl {
public:
    Impl()
        : app_(nil)
        , timer_(nil)
        , delegate_(nil)
        , initialize_function_([]() {})
        , update_function_([]() {})
        , terminate_function_([]() {}) {
        app_ = [NSApplication sharedApplication];
        delegate_ = [[ApplicationDelegate alloc] init];
        [app_ setDelegate:delegate_];
        [app_ setActivationPolicy:NSApplicationActivationPolicyRegular];

        main_thread_ = ThreadPool::makeUnique("Main", 1);
        exit_flag_ = 0;
    }

    ~Impl() { [app_ terminate:app_]; }

    void setInitializeFunction(const std::function< void(void)> &func) { initialize_function_ = func; }

    void setUpdateFunction(const std::function< void(void)> &func) { update_function_ = func; }

    void setTerminateFunction(const std::function< void(void)> &func) { terminate_function_ = func; }

    temp::Int32 run() {
        initialize_function_();
        // main_thread_.reset(new std::thread(std::bind(&Impl::mainLoop, this)));
        auto future = main_thread_->pushJob([this](){mainLoop(); });
        [app_ run];
        exit_flag_ = 1;
        // main_thread_->join();
        future.wait();
        terminate_function_();
        return 0;
    }

    void exit() {
        exit_flag_ = 1;
        [app_ stop:app_];
    }
    
    ThreadPoolSPtr getMainThread() const { return main_thread_; }

private:
    NSApplication *app_;
    NSTimer *timer_;
    ApplicationDelegate *delegate_;

    //using ThreadUPtr = std::unique_ptr< std::thread >;
    //ThreadUPtr main_thread_;
    temp::system::ThreadPool::SPtr main_thread_;
    std::atomic_char exit_flag_;
    std::function< void(void)> initialize_function_;
    std::function< void(void)> update_function_;
    std::function< void(void)> terminate_function_;

    void mainLoop() {
        while (!exit_flag_) {
            update_function_();
        }
    }
};

Application::Application() : impl_(new Impl) {}

Application::~Application() {}

void Application::setInitializeFunction(const std::function< void(void)> &func) { impl_->setInitializeFunction(func); }

void Application::setUpdateFunction(const std::function< void(void)> &func) { impl_->setUpdateFunction(func); }

void Application::setTerminateFunction(const std::function< void(void)> &func) { impl_->setTerminateFunction(func); }

Int32 Application::run() { return impl_->run(); }

void Application::exit() { return impl_->exit(); }
    
ThreadPool::SPtr Application::getMainThread() const { return impl_->getMainThread(); }
    
Application::SPtr Application::create() {
    struct Creator : public Application {
    };
    
    auto p = std::make_shared< Creator >();
    return std::move(p);
}
    
}
}
