#pragma once

#include <memory>

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {

class SwapChain;
using SwapChainSPtr = std::shared_ptr<SwapChain>;

class Device {
 public:
  Device() {}

  virtual ~Device() = default;

  virtual SwapChainSPtr CreateSwapChain(const void* window) const = 0;

  virtual SwapChainSPtr default_swap_chain() const = 0;

  virtual GraphicsApi graphics_api() const = 0;
};

using DeviceSPtr = std::shared_ptr<Device>;

DeviceSPtr CreateDevice(GraphicsApi api, const void* default_window);

}  // namespace graphics
}  // namespace temp
