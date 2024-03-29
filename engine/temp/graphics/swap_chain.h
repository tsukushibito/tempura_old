#pragma once

#include <memory>

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {

class SwapChain {
 public:
  virtual ~SwapChain() = default;

  virtual void Present() = 0;

  virtual GraphicsApi graphics_api() const = 0;
};

using SwapChainSPtr = std::shared_ptr<SwapChain>;

}  // namespace graphics
}  // namespace temp
