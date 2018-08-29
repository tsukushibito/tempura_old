#pragma once
#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include <utility>
#include <vulkan/vulkan.hpp>
#include "temp/core/core.h"
#include "temp/rendering/renderer_base.h"
#include "temp/resource/resource_manager.h"

namespace temp {
namespace rendering {
namespace vulkan {

using UniqueDebugUtilsMessengerEXT =
    vk::UniqueHandle<vk::DebugUtilsMessengerEXT, vk::DispatchLoaderDynamic>;
using UniqueSurfaceKHR =
    vk::UniqueHandle<vk::SurfaceKHR, vk::DispatchLoaderDynamic>;

class VkRenderer : public RendererBase<VkRenderer> {
  friend class SmartPointerType<VkRenderer>;

 private:
  VkRenderer(const TaskManager::SPtr& task_manager,
             const resource::ResourceManager::SPtr& resource_manager);

 public:
  void Render();

 private:
  TaskManager::SPtr task_manager_;
  resource::ResourceManager::SPtr resource_manager_;

  const void* window_handle_;

  vk::UniqueInstance instance_;
  vk::UniqueDevice device_;
  vk::DispatchLoaderDynamic dispatch_loader_dynamic_;
  UniqueDebugUtilsMessengerEXT messenger_;
  UniqueSurfaceKHR surface_;
};
}  // namespace vulkan
using Renderer = RendererBase<vulkan::VkRenderer>;

}  // namespace rendering
}  // namespace temp

#endif
