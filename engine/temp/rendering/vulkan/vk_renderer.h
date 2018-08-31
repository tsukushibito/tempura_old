#pragma once
#include "temp/core/core.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include <utility>
#include <vulkan/vulkan.hpp>
#include "temp/rendering/renderer.h"

namespace temp {
namespace rendering {
namespace vulkan {

using UniqueDebugUtilsMessengerEXT =
    vk::UniqueHandle<vk::DebugUtilsMessengerEXT, vk::DispatchLoaderDynamic>;
using UniqueSurfaceKHR =
    vk::UniqueHandle<vk::SurfaceKHR, vk::DispatchLoaderDynamic>;

using DispatchLoaderDynamicUPtr = std::unique_ptr<vk::DispatchLoaderDynamic>;

class VkRenderer : public Renderer, public SmartPointerType<VkRenderer> {
  friend class SmartPointerType<VkRenderer>;

 private:
  VkRenderer(const TaskManagerSPtr& task_manager,
             const ResourceManagerSPtr& resource_manager);

 public:
  ~VkRenderer();

  SwapChainSPtr CreateSwapChain(const void* window) override;

  void Render() override;

  const vk::UniqueInstance& instance() const { return instance_; }
  const vk::UniqueDevice& device() const { return device_; }
  const vk::DispatchLoaderDynamic& dispatch() const { return *dispatch_; }

 private:
  vk::UniqueInstance instance_;
  vk::UniqueDevice device_;
  UniqueDebugUtilsMessengerEXT messenger_;
  DispatchLoaderDynamicUPtr dispatch_;
};

}  // namespace vulkan
}  // namespace rendering
}  // namespace temp

#endif
