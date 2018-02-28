#include <memory>
#include "temp/app/application.h"
#include "temp/common/common.h"
#include "temp/core/core.h"
#include "temp/graphics/graphics.h"

extern "C" {
TEMP_DECLSPEC void tempCreateEngine();
TEMP_DECLSPEC void tempDestroyEngine();
}

namespace temp {
TEMP_DECLSPEC temp::app::ApplicationUPtr createApplication();
}  // namespace temp