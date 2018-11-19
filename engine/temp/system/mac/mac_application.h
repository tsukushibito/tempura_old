#pragma once
#include "temp/system/application_base.h"
#ifdef TEMP_PLATFORM_MAC

namespace temp {
namespace system {
namespace mac {

class MacApplication : public ApplicationBase,
                       public SmartPointerType<MacApplication> {
  friend class SmartPointerType<MacApplication>;

 private:
  MacApplication();

 public:
  virtual ~MacApplication();

  std::int32_t Run() override;
  void Exit() override;

 private:
  void MainLoop();

 private:
  struct Properties;
  std::unique_ptr<Properties> properties_;
};
}  // namespace mac
using Application = mac::MacApplication;

}  // namespace system
}  // namespace temp
#endif
