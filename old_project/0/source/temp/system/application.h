/**
 * @file application.h
 * @brief application class
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-21
 */

#include <functional>
#include <memory>

#include "temp/type.h"

namespace temp {
namespace system {

class ThreadPool;

class Application : public SmartPointerObject<Application> {
private:
    using ThreadPoolSPtr = std::shared_ptr<ThreadPool>;

    Application();

public:
    ~Application();

public:
    void setInitializeFunction(const std::function<void(void)> &func);
    void setUpdateFunction(const std::function<void(void)> &func);
    void setTerminateFunction(const std::function<void(void)> &func);

    Int32 run();
    void  exit();

    ThreadPoolSPtr getMainThread() const;

private:
    class Impl;
    std::unique_ptr<Impl> impl_;

public:
    static SPtr create();
};
} // namespace system
} // namespace temp
