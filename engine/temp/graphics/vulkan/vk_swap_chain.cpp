#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include "temp/graphics/vulkan/vk_device.h"
#include "temp/graphics/vulkan/vk_swap_chain.h"
#if defined(TEMP_PLATFORM_MAC)
#include "temp/system/mac/mac_utility.h"
#endif

namespace {
vk::UniqueSurfaceKHR CreateSurface(const vk::UniqueInstance& instance,
                                   const void* window) {
  vk::UniqueSurfaceKHR surface;
#if defined(VK_USE_PLATFORM_MACOS_MVK)
  void* view_handle = temp::system::mac::GetViewHandle(window, true);
  vk::MacOSSurfaceCreateInfoMVK create_info;
  create_info.pView = view_handle;
  surface = instance->createMacOSSurfaceMVKUnique(create_info);
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
#elif defined(__ANDROID__)
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
#else
#endif  // _WIN32
  return surface;
}
}  // namespace

namespace temp {
namespace graphics {
namespace vulkan {

VkSwapChain::VkSwapChain(const VkDevice& device, const void* window) {
  surface_ = CreateSurface(device.instance(), window);
  device.physical_device().getSurfaceSupportKHR(device.queue_family_index(), *surface_);
}

VkSwapChain::~VkSwapChain() {}

void VkSwapChain::Present() {}
}  // namespace vulkan
}  // namespace graphics
}  // namespace temp

#endif  // TEMP_GRAPHICS_VULKAN
