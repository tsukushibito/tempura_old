#pragma once
#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include <utility>
#include <vulkan/vulkan.hpp>
#include "temp/rendering/renderer.h"

namespace temp {
namespace rendering {

using UniqueDebugUtilsMessengerEXT =
    vk::UniqueHandle<vk::DebugUtilsMessengerEXT, vk::DispatchLoaderDynamic>;
using UniqueSurfaceKHR =
    vk::UniqueHandle<vk::SurfaceKHR, vk::DispatchLoaderDynamic>;

using DispatchLoaderDynamicUPtr = std::unique_ptr<vk::DispatchLoaderDynamic>;

class Renderer::Impl {
 public:
  Impl(Renderer& parent, vk::UniqueInstance& instance, vk::UniqueDevice& device,
       UniqueDebugUtilsMessengerEXT& messenger,
       DispatchLoaderDynamicUPtr& dispatch);
  ~Impl();

  void Render();

  Renderer& parent_;
  vk::UniqueInstance instance_;
  vk::UniqueDevice device_;
  UniqueDebugUtilsMessengerEXT messenger_;
  DispatchLoaderDynamicUPtr dispatch_loader_dynamic_;
};

}  // namespace rendering
}  // namespace temp

#endif
