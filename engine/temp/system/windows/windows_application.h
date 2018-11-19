
#pragma once
#include "temp/system/application_base.h"
#ifdef TEMP_PLATFORM_WINDOWS

namespace temp {
namespace system {
namespace windows {

class WindowsApplication : public ApplicationBase,
                           public SmartPointerType<WindowsApplication> {
  friend class SmartPointerType<WindowsApplication>;

 private:
  WindowsApplication();

 public:
  virtual ~WindowsApplication();

  std::int32_t Run() override;
  void Exit() override;

 private:
  void Init();
  void Term();
};
}  // namespace windows
using Application = windows::WindowsApplication;

}  // namespace system
}  // namespace temp
#endif
