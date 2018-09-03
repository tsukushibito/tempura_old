#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include "temp/graphics/vulkan/vk_device.h"
#include "temp/graphics/vulkan/vk_swap_chain.h"
#if defined(TEMP_PLATFORM_MAC)
#include "temp/system/mac/mac_utility.h"
#endif

namespace {
const char* kVkSwapChainTag = "kVkSwapChain";

temp::graphics::vulkan::UniqueSurfaceKHR CreateSurface(
    const vk::UniqueInstance& instance,
    const vk::DispatchLoaderDynamic& dispatch, const void* window) {
  temp::graphics::vulkan::UniqueSurfaceKHR surface;
#if defined(VK_USE_PLATFORM_MACOS_MVK)
  void* view_handle = temp::system::mac::GetViewHandle(window, true);
  vk::MacOSSurfaceCreateInfoMVK create_info;
  create_info.pView = view_handle;
  surface =
      instance->createMacOSSurfaceMVKUnique(create_info, nullptr, dispatch);
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
#elif defined(__ANDROID__)
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
#else
#endif  // _WIN32
  return surface;
}

vk::SurfaceFormatKHR ChooseFormat(
    const std::vector<vk::SurfaceFormatKHR>& formats) {
  if (formats.size() == 1 && formats[0].format == vk::Format::eUndefined) {
    return {vk::Format::eB8G8R8A8Unorm, vk::ColorSpaceKHR::eSrgbNonlinear};
  }
  for (auto& format : formats) {
    if (format.format == vk::Format::eB8G8R8A8Unorm &&
        format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
      return format;
  }

  return formats[0];
}

vk::Extent2D ChooseExtent(const vk::SurfaceCapabilitiesKHR& capabilities) {
  if (capabilities.currentExtent.width !=
      std::numeric_limits<uint32_t>::max()) {
    return capabilities.currentExtent;
  } else {
    VkExtent2D actual_extent = {1080, 720};

    actual_extent.width = std::max(
        capabilities.minImageExtent.width,
        std::min(capabilities.maxImageExtent.width, actual_extent.width));
    actual_extent.height = std::max(
        capabilities.minImageExtent.height,
        std::min(capabilities.maxImageExtent.height, actual_extent.height));

    return actual_extent;
  }
}

vk::PresentModeKHR ChoosePresentMode(
    const std::vector<vk::PresentModeKHR>& present_modes) {
  vk::PresentModeKHR mode = vk::PresentModeKHR::eImmediate;
  for (const auto& present_mode : present_modes) {
    if (present_mode == vk::PresentModeKHR::eMailbox) {
      mode = vk::PresentModeKHR::eMailbox;
      break;
    } else if (mode == vk::PresentModeKHR::eImmediate &&
               present_mode == vk::PresentModeKHR::eFifo) {
      mode = vk::PresentModeKHR::eFifo;
    }
  }

  return mode;
}

temp::graphics::vulkan::UniqueSwapchainKHR CreateSwapChain(
    const vk::PhysicalDevice& physical_device, const vk::UniqueDevice& device,
    temp::UInt32 queue_family_index,
    const temp::graphics::vulkan::UniqueSurfaceKHR& surface,
    const vk::DispatchLoaderDynamic& dispatch) {
  auto capabilities = physical_device.getSurfaceCapabilitiesKHR(*surface);
  auto formats = physical_device.getSurfaceFormatsKHR(*surface);
  auto present_modes = physical_device.getSurfacePresentModesKHR(*surface);

  auto format = ChooseFormat(formats);
  auto extent = ChooseExtent(capabilities);
  auto present_mode = ChoosePresentMode(present_modes);

  vk::SwapchainCreateInfoKHR create_info;
  create_info.surface = *surface;
  create_info.minImageCount = capabilities.maxImageCount;
  create_info.imageFormat = format.format;
  create_info.imageColorSpace = format.colorSpace;
  create_info.imageExtent = extent;
  create_info.imageArrayLayers = 1;
  create_info.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;
  create_info.imageSharingMode = vk::SharingMode::eExclusive;
  create_info.queueFamilyIndexCount = 0;
  create_info.pQueueFamilyIndices = nullptr;
  create_info.preTransform = capabilities.currentTransform;
  create_info.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
  create_info.presentMode = present_mode;
  create_info.clipped = true;
  create_info.oldSwapchain = nullptr;

  return device->createSwapchainKHRUnique(create_info, nullptr, dispatch);
}
}  // namespace

namespace temp {
namespace graphics {
namespace vulkan {

VkSwapChain::VkSwapChain(const VkDevice& device, const void* window) {
  surface_ = CreateSurface(device.instance(), device.dispatch(), window);
  auto is_supported = device.physical_device().getSurfaceSupportKHR(
      device.queue_family_indices().graphics_family, *surface_);
  if (!is_supported) {
    TEMP_LOG_ERROR(kVkSwapChainTag, "Surface is not supported.");
    return;
  }
  swapchain_ = CreateSwapChain(device.physical_device(), device.device(),
                               device.queue_family_indices().graphics_family,
                               surface_, device.dispatch());
}

VkSwapChain::~VkSwapChain() {}

void VkSwapChain::Present() {}
}  // namespace vulkan
}  // namespace graphics
}  // namespace temp

#endif  // TEMP_GRAPHICS_VULKAN
