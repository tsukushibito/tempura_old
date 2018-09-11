#include "temp/rendering/vulkan/vk_renderer.h"
#include "temp/graphics/vulkan/vk_device.h"
#include "temp/graphics/vulkan/vk_swap_chain.h"

namespace temp {
namespace rendering {
namespace vulkan {
VkRenderer::VkRenderer(const temp::graphics::DeviceSPtr& device) {
  TEMP_ASSERT(device->graphics_api() == graphics::GraphicsApi::kVulkan,
              "device's api must be Vulkan!");
  device_ = std::dynamic_pointer_cast<graphics::vulkan::VkDevice>(device);
  swap_chain_ = std::dynamic_pointer_cast<graphics::vulkan::VkSwapChain>(
      device_->default_swap_chain());
}

VkRenderer::~VkRenderer() {}

void VkRenderer::Draw() {}

}  // namespace vulkan
}  // namespace rendering
}  // namespace temp