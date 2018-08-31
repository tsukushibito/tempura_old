#include "temp/rendering/renderer.h"
#include "temp/core/core.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include "temp/rendering/vulkan/vk_renderer.h"
#endif

namespace temp {
namespace rendering {
RendererSPtr CreateRenderer(GraphicsApi api,
                            const TaskManagerSPtr& task_manager,
                            const ResourceManagerSPtr& resource_manager) {
  switch (api) {
    case GraphicsApi::kVulkan:
#if defined(TEMP_GRAPHICS_VULKAN)
      return vulkan::VkRenderer::MakeShared(task_manager, resource_manager);
#else
      return nullptr;
#endif
    case GraphicsApi::kOpenGl:
      break;
    case GraphicsApi::kD3d12:
      break;
    case GraphicsApi::kD3d11:
      break;
    default:
      TEMP_ASSERT(false, "");
      break;
  }
  return nullptr;
}
}  // namespace rendering
}  // namespace temp
