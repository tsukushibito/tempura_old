#pragma once
#include <functional>
#include "temp/core/core.h"

namespace temp {
namespace system {

class ApplicationBase {
 public:
  ApplicationBase() {}
  virtual ~ApplicationBase(){};

  virtual std::int32_t Run() = 0;
  virtual void Exit() = 0;

  std::function<void(void)> &on_initialize() { return on_initialize_; }
  std::function<void(void)> &on_update() { return on_update_; }
  std::function<void(void)> &on_terminate() { return on_terminate_; }
  void *native_window_handle() const { return native_window_handle_; }

 protected:
  std::function<void(void)> on_initialize_ = []() {};
  std::function<void(void)> on_update_ = []() {};
  std::function<void(void)> on_terminate_ = []() {};
  void *native_window_handle_ = nullptr;
};

using ApplicationSPtr = std::shared_ptr<ApplicationBase>;

}  // namespace system
}  // namespace temp
