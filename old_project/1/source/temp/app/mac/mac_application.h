#pragma once
#include "temp/app/application.h"
#include "temp/common/common.h"
#ifdef TEMP_PLATFORM_MAC

namespace temp {
namespace app {
namespace mac {

class MacApplication : public Application {
 public:
  MacApplication();
  virtual ~MacApplication();

  void setOnInitializeCallback(
      const std::function<void(void)> &on_initialize) override;
  void setOnUpdateCallback(const std::function<void(void)> &on_update) override;
  void setOnTerminateCallback(
      const std::function<void(void)> &on_terminate) override;
  Int32 run() override;
  void exit() override;
  void *getNativeWindowHandle() override;

 private:
  void mainLoop();

 private:
  struct Properties;
  std::unique_ptr<Properties> properties_;
};
}  // namespace mac
}  // namespace app
}  // namespace temp
#endif