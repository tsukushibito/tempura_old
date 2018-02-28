#include "temp/app/application.h"
#include "temp/common/common.h"
#include "temp/core/core.h"
#include "temp/graphics/graphics.h"

namespace temp {

class Tempura {
 public:
  Tempura() = default;
  ~Tempura() = default;

  virtual void update() = 0;
};

using TempUPtr = std::unique_ptr<Tempura>;

TEMP_DECLSPEC TempUPtr create();
TEMP_DECLSPEC temp::app::ApplicationUPtr createApplication();

}  // namespace temp