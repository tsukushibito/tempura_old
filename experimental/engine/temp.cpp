#define TEMP_EXPORT
#include "temp.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include "temp/app/windows/windows_application.h"
#else
#endif

namespace temp {

class TempuraImpl : public Tempura {
 public:
  void update(){/*core::Logger::trace("Tempura", "update");*/};
};

TEMP_DECLSPEC TempUPtr create() { return std::make_unique<TempuraImpl>(); }

TEMP_DECLSPEC temp::app::ApplicationUPtr createApplication() {
#ifdef TEMP_PLATFORM_WINDOWS
  return std::make_unique<temp::app::windows::WindowsApplication>();
#else
  return nullptr;
#endif
}
}  // namespace temp