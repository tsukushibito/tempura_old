#include <temp.h>
#include <functional>
#include <memory>

namespace temp {
namespace app {

class Application {
 public:
  Application();
  ~Application();

  void setOnInitializeCallback(const std::function<void(void)> &on_initialize);
  void setOnUpdateCallback(const std::function<void(void)> &on_update);
  void setOnTerminateCallback(const std::function<void(void)> &on_terminate);

  Int32 run();

  void exit();

  void *getNativeWindowHandle();

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};
}  // namespace app
}  // namespace temp