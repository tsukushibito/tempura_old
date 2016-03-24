#include "temp/define.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include "temp/system/application.h"

namespace temp {
namespace system {

class Application::Impl {
public:
    Impl() {
        initialize_function_ = [](){};
        update_function_ = [](){};
        terminate_function_ = [](){};
        exit_flag_ = 0;
    }

    void setInitializeFunction(const std::function<void(void)> &func) { initialize_function_ = func; }

    void setUpdateFunction(const std::function<void(void)> &func) { update_function_ = func; }

    void setTerminateFunction(const std::function<void(void)> &func) { terminate_function_ = func; }

    Int32 run() {
        initialize_function_();

        main_thread_.reset(new std::thread(std::bind(&Impl::mainLoop, this)));
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        exit_flag_ = 1;
        main_thread_->join();

        terminate_function_();

        return static_cast< Int32 >(msg.wParam);
    }

    void exit() { exit_flag_ = true; }

private:
    using ThreadUPtr = std::unique_ptr< std::thread >;
    ThreadUPtr main_thread_;
    std::atomic_char exit_flag_;
    std::function<void(void)> initialize_function_;
    std::function<void(void)> update_function_;
    std::function<void(void)> terminate_function_;

    void mainLoop() {
        while (exit_flag_ == 0) {
            update_function_();
        }
    }
};

Application::Application()
    : impl_(new Impl) {}

Application::~Application() {}

void Application::setInitializeFunction(const std::function<void(void)> &func) {
    impl_->setInitializeFunction(func);
}

void Application::setUpdateFunction(const std::function<void(void)> &func) {
    impl_->setUpdateFunction(func);
}

void Application::setTerminateFunction(const std::function<void(void)> &func) {
    impl_->setTerminateFunction(func);
}

Int32 Application::run() { return impl_->run(); }

void Application::exit() { return impl_->exit(); }

Application::SPtr Application::create() {
    struct Creator : public Application {
		Creator() : Application() { }
    };

    auto p = std::make_shared< Creator >();
    return std::move(p);
}

}
}
#endif
