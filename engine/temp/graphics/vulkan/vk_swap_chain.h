#pragma once
#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include <vulkan/vulkan.hpp>
#include "temp/core/core.h"
#include "temp/graphics/swap_chain.h"

namespace temp {
namespace graphics {
namespace vulkan {

class VkDevice;

class VkSwapChain : public SwapChain, public SmartPointerType<VkSwapChain> {
  friend class SmartPointerType<VkSwapChain>;

 private:
  VkSwapChain(const VkDevice& device, const void* window);

 public:
  ~VkSwapChain();

  void Present() override;

  vk::UniqueSurfaceKHR surface_;
};
}  // namespace vulkan
}  // namespace graphics
}  // namespace temp

#endif
