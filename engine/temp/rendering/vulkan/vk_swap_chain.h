#pragma once
#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include <vulkan/vulkan.hpp>
#include "temp/core/core.h"
#include "temp/rendering/swap_chain_base.h"
#include "temp/rendering/vulkan/vk_renderer.h"
namespace temp {
namespace rendering {
namespace vulkan {
class VkSwapChain : public SwapChainBase<VkSwapChain> {
  friend class SmartPointerType<VkSwapChain>;

 private:
  VkSwapChain(const VkRenderer::SPtr& renderer, void* window_handle) {}

 public:
  void Present() {}

 private:
  vk::UniqueSurfaceKHR surface_;
};
}  // namespace vulkan
using SwapChain = SwapChainBase<vulkan::VkSwapChain>;

}  // namespace rendering
}  // namespace temp
#endif
