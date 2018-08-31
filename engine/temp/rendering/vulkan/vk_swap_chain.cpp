#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include "temp/rendering/vulkan/vk_renderer.h"
#include "temp/rendering/vulkan/vk_swap_chain.h"
#if defined(TEMP_PLATFORM_MAC)
#include "temp/system/mac/mac_utility.h"
#endif

namespace {
vk::UniqueSurfaceKHR CreateSurface(const vk::UniqueInstance& instance,
                                   const vk::DispatchLoaderDynamic& dispatch,
                                   const void* native_window_handle) {
#if defined(VK_USE_PLATFORM_MACOS_MVK)
  void* view_handle =
      temp::system::mac::GetViewHandle(native_window_handle, true);
  vk::MacOSSurfaceCreateInfoMVK create_info;
  create_info.pView = view_handle;
  return instance->createMacOSSurfaceMVKUnique(create_info);
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
#elif defined(__ANDROID__)
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
#else
#endif  // _WIN32
}
}  // namespace

namespace temp {
namespace rendering {
namespace vulkan {

VkSwapChain::VkSwapChain(const vk::UniqueInstance& instance,
                         const vk::DispatchLoaderDynamic& dispatch,
                         const void* window) {
  surface_ = CreateSurface(instance, dispatch, window);
}

VkSwapChain::~VkSwapChain() {}

void VkSwapChain::Present() {}
}  // namespace vulkan
}  // namespace rendering
}  // namespace temp

#endif  // TEMP_GRAPHICS_VULKAN
