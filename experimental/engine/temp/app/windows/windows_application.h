#pragma once
#include "temp/app/application.h"
#include "temp/common/common.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>

namespace temp {
namespace app {
namespace windows {

class WindowsApplication : public Application {
 public:
  WindowsApplication();
  virtual ~WindowsApplication();

  void setOnInitializeCallback(const std::function<void(void)> &on_initialize);
  void setOnUpdateCallback(const std::function<void(void)> &on_update);
  void setOnTerminateCallback(const std::function<void(void)> &on_terminate);
  Int32 run();
  void exit();
  void *getNativeWindowHandle();

  void init();
  void term();

 private:
  std::function<void(void)> on_initialize_ = []() {};
  std::function<void(void)> on_update_ = []() {};
  std::function<void(void)> on_terminate_ = []() {};

  HWND window_handle_;
};
}  // namespace windows
}  // namespace app
}  // namespace temp
#endif