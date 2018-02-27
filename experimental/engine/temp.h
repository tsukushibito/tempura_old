#include <memory>
#include "temp/app/application.h"
#include "temp/common/define.h"
#include "temp/common/type.h"

extern "C" {
TEMP_DECLSPEC temp::app::IApplication* tempCreateApplication();
TEMP_DECLSPEC void tempDestroyApplication(temp::app::IApplication* app);
TEMP_DECLSPEC void tempCreateEngine();
TEMP_DECLSPEC void tempDestroyEngine();
}

namespace temp {
using Application =
    std::unique_ptr<temp::app::IApplication, decltype(&tempDestroyApplication)>;

template <typename T = void>
Application createApplication() {
  auto app = Application(tempCreateApplication(), tempDestroyApplication);
  return std::move(app);
}
}  // namespace temp