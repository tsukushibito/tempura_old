#pragma once
#include "temp/app/application.h"
#include "temp/asset/asset.h"
#include "temp/common/common.h"
#include "temp/core/core.h"
#include "temp/graphics/graphics.h"
#include "temp/math/math.h"
#include "temp/renderer/renderer.h"
#include "temp/resource/resource.h"

namespace temp {

class Tempura {
 public:
  Tempura() = default;
  ~Tempura() = default;

  virtual void update() = 0;
  virtual graphics::Device::SPtr graphicsDevice() = 0;
  virtual resource::ResourceManager::SPtr resourceManager() = 0;
};

using TempSPtr = std::shared_ptr<Tempura>;

TEMP_DECLSPEC TempSPtr create(void* window_handle);

TEMP_DECLSPEC temp::app::ApplicationSPtr createApplication();

}  // namespace temp
