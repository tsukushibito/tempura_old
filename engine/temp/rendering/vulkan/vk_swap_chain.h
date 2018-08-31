#pragma once
#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include <vulkan/vulkan.hpp>
#include "temp/core/core.h"
#include "temp/rendering/swap_chain.h"

namespace temp {
namespace rendering {
namespace vulkan {

class VkRenderer;

class VkSwapChain : public SwapChain, public SmartPointerType<VkSwapChain> {
  friend class SmartPointerType<VkSwapChain>;

 private:
  VkSwapChain(const vk::UniqueInstance& instance,
              const vk::DispatchLoaderDynamic& dispatch, const void* window);

 public:
  ~VkSwapChain();

  void Present() override;

  vk::UniqueSurfaceKHR surface_;
};
}  // namespace vulkan
}  // namespace rendering
}  // namespace temp

#endif
