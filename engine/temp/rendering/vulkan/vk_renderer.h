#pragma once
#include "temp/graphics/vulkan/vk_device.h"
#include "temp/rendering/renderer.h"

namespace temp {
namespace rendering {
namespace vulkan {

class VkRenderer : public Renderer, public SmartPointerType<VkRenderer> {
  friend class SmartPointerType<VkRenderer>;

 private:
  VkRenderer(const temp::graphics::DeviceSPtr& device);

 public:
  ~VkRenderer();

  void Draw();

 private:
  temp::graphics::vulkan::VkDevice::SPtr device_;
  temp::graphics::vulkan::VkSwapChain::SPtr swap_chain_;

  vk::Queue graphics_queue_;
  vk::Queue present_queue_;

  std::vector<CameraWPtr> camera_list_;
  std::vector<ModelWPtr> model_list_;
};
}  // namespace vulkan
}  // namespace rendering
}  // namespace temp
