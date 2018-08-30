#pragma once
#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include <vulkan/vulkan.hpp>
#include "temp/core/core.h"
#include "temp/rendering/swap_chain.h"

namespace temp {
namespace rendering {

class SwapChain::Impl {
 public:
  Impl(SwapChain& parent, vk::UniqueSurfaceKHR surface);
  ~Impl();

  void Present();

  SwapChain& parent_;

  vk::UniqueSurfaceKHR surface;
};
}  // namespace rendering
}  // namespace temp

#endif
