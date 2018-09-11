#include "temp/rendering/renderer.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include "temp/rendering/vulkan/vk_renderer.h"
#endif
#if defined(TEMP_GRAPHICS_OPENGL)
#endif

namespace temp {
namespace rendering {

RendererSPtr CreateRenderer(const temp::graphics::DeviceSPtr& device) {
  using namespace temp::graphics;
  RendererSPtr renderer;

  auto api = device->graphics_api();
  switch (api) {
#if defined(TEMP_GRAPHICS_VULKAN)
    case GraphicsApi::kVulkan:
      renderer = vulkan::VkRenderer::MakeShared(device);
      break;
#endif
#if defined(TEMP_GRAPHICS_OPENGL)
    case GraphicsApi::kOpenGl:
      break;
#endif
    default:
      break;
  }

  return renderer;
}

}  // namespace rendering
}  // namespace temp