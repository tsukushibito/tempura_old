﻿#pragma once
#include <functional>
#include <memory>
#include "temp/common/define.h"
#include "temp/common/type.h"

namespace temp {
namespace app {

class Application {
 public:
  Application() {}
  virtual ~Application(){};

  virtual void setOnInitializeCallback(
      const std::function<void(void)> &on_initialize) = 0;
  virtual void setOnUpdateCallback(
      const std::function<void(void)> &on_update) = 0;
  virtual void setOnTerminateCallback(
      const std::function<void(void)> &on_terminate) = 0;
  virtual Int32 run() = 0;
  virtual void exit() = 0;
  virtual void *getNativeWindowHandle() = 0;
};

using ApplicationSPtr = std::shared_ptr<Application>;

}  // namespace app
}  // namespace temp