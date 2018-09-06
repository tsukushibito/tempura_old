#pragma once

#include <memory>

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {

class FragmentShader {
 public:
  virtual ~FragmentShader() = default;

  virtual GraphicsApi graphics_api() const = 0;
};

using FragmentShaderSPtr = std::shared_ptr<FragmentShader>;

}  // namespace graphics
}  // namespace temp