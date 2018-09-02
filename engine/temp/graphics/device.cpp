#include "temp/graphics/device.h"
#include "temp/core/core.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include "temp/graphics/vulkan/vk_device.h"
#endif

namespace temp {
namespace graphics {
DeviceSPtr CreateDevice(GraphicsApi api) {
  switch (api) {
    case GraphicsApi::kVulkan:
#if defined(TEMP_GRAPHICS_VULKAN)
      return vulkan::VkDevice::MakeShared();
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
}  // namespace graphics
}  // namespace temp
