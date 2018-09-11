#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include "temp/graphics/vulkan/vk_device.h"
#include "temp/graphics/vulkan/vk_swap_chain.h"
#if defined(TEMP_PLATFORM_MAC)
#include "temp/system/mac/mac_utility.h"
#endif
#if defined(TEMP_PLATFORM_WINDOWS)
#if defined(max)
#undef max
#endif
#if defined(min)
#undef min
#endif
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
  HWND hwnd = reinterpret_cast<HWND>(const_cast<void*>(window));
  HINSTANCE hinstance = GetModuleHandle(NULL);
  vk::Win32SurfaceCreateInfoKHR create_info;
  create_info.hwnd = hwnd;
  create_info.hinstance = hinstance;
  surface =
      instance->createWin32SurfaceKHRUnique(create_info, nullptr, dispatch);
#elif defined(__ANDROID__)
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
#else
#endif  // _WIN32
  return surface;
}

vk::SurfaceFormatKHR ChooseFormat(
    const vk::PhysicalDevice& physical_device,
    const temp::graphics::vulkan::UniqueSurfaceKHR& surface) {
  auto formats = physical_device.getSurfaceFormatsKHR(*surface);

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

vk::Extent2D ChooseExtent(
    const vk::PhysicalDevice& physical_device,
    const temp::graphics::vulkan::UniqueSurfaceKHR& surface) {
  auto capabilities = physical_device.getSurfaceCapabilitiesKHR(*surface);
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
    const vk::PhysicalDevice& physical_device,
    const temp::graphics::vulkan::UniqueSurfaceKHR& surface) {
  auto present_modes = physical_device.getSurfacePresentModesKHR(*surface);
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
    const vk::UniqueDevice& device,
    const temp::graphics::vulkan::UniqueSurfaceKHR& surface,
    vk::SurfaceFormatKHR format, vk::Extent2D extent,
    const vk::SurfaceCapabilitiesKHR& capabilities,
    vk::PresentModeKHR present_mode,
    const vk::DispatchLoaderDynamic& dispatch) {
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

std::vector<vk::UniqueImageView> CreateImageViews(
    const vk::UniqueDevice& device, const std::vector<vk::Image>& images,
    vk::Format format) {
  std::vector<vk::UniqueImageView> image_views;
  for (auto&& image : images) {
    vk::ImageViewCreateInfo create_info;
    create_info.image = image;
    create_info.viewType = vk::ImageViewType::e2D;
    create_info.format = format;
    create_info.components.r = vk::ComponentSwizzle::eIdentity;
    create_info.components.g = vk::ComponentSwizzle::eIdentity;
    create_info.components.b = vk::ComponentSwizzle::eIdentity;
    create_info.components.a = vk::ComponentSwizzle::eIdentity;
    create_info.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    create_info.subresourceRange.baseMipLevel = 0;
    create_info.subresourceRange.levelCount = 1;
    create_info.subresourceRange.baseArrayLayer = 0;
    create_info.subresourceRange.layerCount = 1;
    image_views.emplace_back(device->createImageViewUnique(create_info));
  }

  return image_views;
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

  format_ = ChooseFormat(device.physical_device(), surface_);
  extent_ = ChooseExtent(device.physical_device(), surface_);
  present_mode_ = ChoosePresentMode(device.physical_device(), surface_);
  auto capabilities =
      device.physical_device().getSurfaceCapabilitiesKHR(*surface_);

  swapchain_ = CreateSwapChain(device.device(), surface_, format_, extent_,
                               capabilities, present_mode_, device.dispatch());

  images_ = device.device()->getSwapchainImagesKHR(*swapchain_);

  image_views_ = CreateImageViews(device.device(), images_, format_.format);
}

VkSwapChain::~VkSwapChain() {}

void VkSwapChain::Present() {}
}  // namespace vulkan
}  // namespace graphics
}  // namespace temp

#endif  // TEMP_GRAPHICS_VULKAN
