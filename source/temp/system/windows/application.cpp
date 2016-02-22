﻿#include "temp/define.h"
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
        initializeFunction_ = []() { OutputDebugString("default initialize function called!\n"); };
        updateFunction_ = []() { OutputDebugString("default update function called!\n"); };
        exitFlag_ = 0;
    }

    void setInitializeFunction(const std::function<void(void)> &func) { initializeFunction_ = func; }

    void setUpdateFunction(const std::function<void(void)> &func) { updateFunction_ = func; }

    void setTerminateFunction(const std::function<void(void)> &func) { terminateFunction_ = func; }

    Int32 run() {
        main_thread_.reset(new std::thread(std::bind(&Impl::mainLoop, this)));
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        exitFlag_ = 1;
        main_thread_->join();

        return static_cast< Int32 >(msg.wParam);
    }

    void exit() { exitFlag_ = true; }

private:
    using ThreadUPtr = std::unique_ptr< std::thread >;
    ThreadUPtr main_thread_;
    std::atomic_char exitFlag_;
    InitializeFunction initialize_function_;
    UpdateFunction update_function_;
    TerminateFunction terminate_function_;

    void mainLoop() {
        initialize_function_();

        while (exit_flag_ == 0) {
            update_function_();
        }

        terminate_function_();
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
}
}
#endif:
