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

class Renderer::Impl {
 public:
  Impl(Renderer& parent);
  ~Impl();

  void Render();

  Renderer& parent_;

  struct Holder {
    vk::UniqueInstance instance;
    vk::UniqueDevice device;
    UniqueDebugUtilsMessengerEXT messenger;

    Holder(vk::UniqueInstance& i, vk::UniqueDevice& d,
           UniqueDebugUtilsMessengerEXT& m)
        : instance(std::move(i)),
          device(std::move(d)),
          messenger(std::move(m)) {}
  };

  std::unique_ptr<Holder> h_;

  vk::DispatchLoaderDynamic dispatch_loader_dynamic_;
};

}  // namespace rendering
}  // namespace temp

#endif
