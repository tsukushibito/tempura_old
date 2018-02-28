#include <iostream>
#define TEMP_EXPORT
#include "temp.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include "temp/app/windows/windows_application.h"
#else
#endif

extern "C" {

TEMP_DECLSPEC void tempCreateEngine() {
  std::cout << "tempCreateEngine()" << std::endl;
}

TEMP_DECLSPEC void tempDestroyEngine() {
  std::cout << "tempDestroyEngine()" << std::endl;
}
}

namespace temp {
TEMP_DECLSPEC temp::app::ApplicationUPtr createApplication() {
#ifdef TEMP_PLATFORM_WINDOWS
  return std::make_unique<temp::app::windows::WindowsApplication>();
#else
  return nullptr;
#endif
}
}  // namespace temp