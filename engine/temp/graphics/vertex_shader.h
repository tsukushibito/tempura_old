#pragma once

#include <memory>

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {

class VertexShader {
 public:
  virtual ~VertexShader() = default;

  virtual GraphicsApi graphics_api() const = 0;
};

}  // namespace graphics
}  // namespace temp