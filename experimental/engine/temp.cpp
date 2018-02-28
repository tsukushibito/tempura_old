#include <memory>
#define TEMP_EXPORT
#include "temp.h"
#if defined(TEMP_PLATFORM_WINDOWS)
#include "temp/app/windows/windows_application.h"
#elif defined(TEMP_PLATFORM_MAC)
#include "temp/app/mac/mac_application.h"
#endif

namespace temp {

class TempuraImpl : public Tempura {
 public:
  void update(){/*core::Logger::trace("Tempura", "update");*/};
};

TEMP_DECLSPEC TempSPtr create() { return std::make_shared<TempuraImpl>(); }

TEMP_DECLSPEC temp::app::ApplicationSPtr createApplication() {
#if defined(TEMP_PLATFORM_WINDOWS)
  return std::make_shared<temp::app::windows::WindowsApplication>();
#elif defined(TEMP_PLATFORM_MAC)
  return std::make_shared<temp::app::mac::MacApplication>();
#endif
}
}  // namespace temp
