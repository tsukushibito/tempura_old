#include <memory>
#include "temp/app/application.h"
#include "temp/common/define.h"
#include "temp/common/type.h"

extern "C" {
TEMP_DECLSPEC temp::app::Application* tempCreateApplication();
TEMP_DECLSPEC void tempDestroyApplication(temp::app::Application* app);
TEMP_DECLSPEC void tempCreateEngine();
TEMP_DECLSPEC void tempDestroyEngine();
}

namespace temp {
using AppUPtr =
    std::unique_ptr<temp::app::Application, decltype(&tempDestroyApplication)>;

template <typename T = void>
AppUPtr createApplication() {
  auto app = AppUPtr(tempCreateApplication(), tempDestroyApplication);
  return std::move(app);
}
}  // namespace temp