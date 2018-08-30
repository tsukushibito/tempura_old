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
                                   void* native_window_handle) {
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

SwapChain::Impl::Impl(SwapChain& parent, vk::UniqueSurfaceKHR& surface)
    : parent_(parent), surface_(std::move(surface)) {}

SwapChain::Impl::~Impl() {}

void SwapChain::Impl::Present() {}

SwapChain::SwapChain(const RendererSPtr& renderer, void* native_window_handle) {
  auto surface =
      CreateSurface(renderer->impl_->instance_, *(renderer->impl_->dispatch_),
                    native_window_handle);
  impl_ = reinterpret_cast<Impl*>(&impl_strage_);
  new (impl_) Impl(*this, surface);
}
}  // namespace rendering
}  // namespace temp

#endif  // TEMP_GRAPHICS_VULKAN
