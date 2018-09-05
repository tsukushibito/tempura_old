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
using UniqueSurfaceKHR =
    vk::UniqueHandle<vk::SurfaceKHR, vk::DispatchLoaderDynamic>;
using UniqueSwapchainKHR =
    vk::UniqueHandle<vk::SwapchainKHR, vk::DispatchLoaderDynamic>;

class VkSwapChain : public SwapChain, public SmartPointerType<VkSwapChain> {
  friend class SmartPointerType<VkSwapChain>;

 private:
  VkSwapChain(const VkDevice& device, const void* window);

 public:
  ~VkSwapChain();

  void Present() override;

  GraphicsApi graphics_api() const override { return GraphicsApi::kVulkan; }

  UniqueSurfaceKHR surface_;
  UniqueSwapchainKHR swapchain_;
};
}  // namespace vulkan
}  // namespace graphics
}  // namespace temp

#endif
