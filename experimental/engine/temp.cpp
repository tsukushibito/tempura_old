#include <iostream>
#define TEMP_EXPORT
#include "temp.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include "temp/app/windows/windows_application.h"
namespace {
temp::app::IApplication* createApplication() {
  return new temp::app::windows::WindowsApplication();
}

void destroyApplication(temp::app::IApplication* app) {
  auto win_app = dynamic_cast<temp::app::windows::WindowsApplication*>(app);
  delete win_app;
}
}  // namespace
#else
#endif

extern "C" {

TEMP_DECLSPEC temp::app::IApplication* tempCreateApplication() {
  return createApplication();
}

TEMP_DECLSPEC void tempDestroyApplication(temp::app::IApplication* app) {
  destroyApplication(app);
}

TEMP_DECLSPEC void tempCreateEngine() {
  std::cout << "tempCreateEngine()" << std::endl;
}

TEMP_DECLSPEC void tempDestroyEngine() {
  std::cout << "tempDestroyEngine()" << std::endl;
}
}