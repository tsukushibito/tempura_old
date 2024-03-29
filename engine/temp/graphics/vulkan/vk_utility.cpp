#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include "temp/core/core.h"
#include "temp/graphics/vulkan/vk_utility.h"
namespace temp {
namespace graphics {
namespace vulkan {

const char* kVkUtilityTag = "VkUtility";
const char* kAppName = "TempuraEngine";
const char* kEngineName = "Tempura";

const std::array<const char*, 1> kValidationLayers = {{
    "VK_LAYER_LUNARG_standard_validation",
}};

const std::array<const char*, 3> kInstanceExtensions = {{
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
    VK_KHR_SURFACE_EXTENSION_NAME,
#ifdef __ANDROID__
    VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
#elif defined(_WIN32)
    VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#elif defined(VK_USE_PLATFORM_IOS_MVK)
    VK_MVK_IOS_SURFACE_EXTENSION_NAME,
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
    VK_MVK_MACOS_SURFACE_EXTENSION_NAME,
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
    VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,
#else
    VK_KHR_XCB_SURFACE_EXTENSION_NAME,
#endif
}};

const std::array<const char*, 1> kDeviceExtensions = {{
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
}};

VKAPI_ATTR VkBool32 VKAPI_CALL
DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
              VkDebugUtilsMessageTypeFlagsEXT messageType,
              const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
              void* pUserData) {
  (void)messageType;
  (void)pUserData;
  if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
    TEMP_LOG_ERROR(kVkUtilityTag,
                   fmt::format("Vulkan: {0}", pCallbackData->pMessage));
  } else if (messageSeverity >=
             VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
    TEMP_LOG_WARN(kVkUtilityTag,
                  fmt::format("Vulkan: {0}", pCallbackData->pMessage));
  } else if (messageSeverity >=
             VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
    TEMP_LOG_TRACE(kVkUtilityTag,
                   fmt::format("Vulkan: {0}", pCallbackData->pMessage));
  }

  return VK_FALSE;
}

bool IsValidationLayerSupported() {
  using namespace temp;
  auto available_layers = vk::enumerateInstanceLayerProperties();

  std::string msg = "Supported layers:\n";
  for (auto layer_property : available_layers) {
    msg += std::string(layer_property.layerName) + "\n";
  }
  TEMP_LOG_INFO(kVkUtilityTag, msg);

  for (const char* layer_name : kValidationLayers) {
    bool is_found = false;

    for (const auto& layerProperties : available_layers) {
      if (strcmp(layer_name, layerProperties.layerName) == 0) {
        is_found = true;
        break;
      }
    }

    if (!is_found) {
      return false;
    }
  }

  return true;
}

vk::UniqueInstance CreateInstance() {
  if (!IsValidationLayerSupported()) {
    throw std::runtime_error("validation layers requested, but not available!");
  }

  vk::ApplicationInfo app_info(kAppName, 1, kEngineName, 1, VK_API_VERSION_1_1);
  vk::InstanceCreateInfo create_info({}, &app_info);
  create_info.enabledLayerCount =
      static_cast<std::uint32_t>(kValidationLayers.size());
  create_info.ppEnabledLayerNames = &kValidationLayers[0];
  create_info.enabledExtensionCount =
      static_cast<std::uint32_t>(kInstanceExtensions.size());
  create_info.ppEnabledExtensionNames = &kInstanceExtensions[0];

  return vk::createInstanceUnique(create_info);
}

UniqueDebugUtilsMessengerEXT CreateMessenger(
    vk::UniqueInstance& instance, const vk::DispatchLoaderDynamic& loader) {
  vk::DebugUtilsMessengerCreateFlagsEXT create_flags;

  vk::DebugUtilsMessageSeverityFlagsEXT message_severity =
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;

  vk::DebugUtilsMessageTypeFlagsEXT message_type =
      vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
      vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
      vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;

  vk::DebugUtilsMessengerCreateInfoEXT create_info(
      create_flags, message_severity, message_type, DebugCallback);

  return instance->createDebugUtilsMessengerEXTUnique(create_info, nullptr,
                                                      loader);
}

std::uint32_t RatePhysicalDevice(const vk::PhysicalDevice& physical_device) {
  using namespace temp;

  std::uint32_t score = 0;

  auto device_properties = physical_device.getProperties();

  auto qfp = physical_device.getQueueFamilyProperties();
  auto iter = std::find_if(
      qfp.begin(), qfp.end(), [](const vk::QueueFamilyProperties& prop) {
        return prop.queueFlags & vk::QueueFlagBits::eGraphics;
      });
  if (iter == qfp.end()) {
    return 0;
  }

  // Discrete GPUs have a significant performance advantage
  if (device_properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
    score += 1000;
  }

  // Maximum possible size of textures affects graphics quality
  score += device_properties.limits.maxImageDimension2D;

  auto device_features = physical_device.getFeatures();

  // Application can't function without geometry shaders
  if (device_features.geometryShader) {
    score += 500;
  }

  return score;
}

vk::PhysicalDevice PickPhysicalDevice(const vk::UniqueInstance& instance) {
  using namespace temp;

  auto physical_devices = instance->enumeratePhysicalDevices();
  TEMP_ASSERT(!physical_devices.empty(), "Not found physical devices.");

  struct PhysDevScore {
    PhysDevScore(std::uint32_t s, vk::PhysicalDevice& pd)
        : score(s), physical_device(pd) {}
    std::uint32_t score;
    vk::PhysicalDevice physical_device;
  };
  std::vector<PhysDevScore> pds_list;
  for (auto physical_device : physical_devices) {
    pds_list.emplace_back(RatePhysicalDevice(physical_device), physical_device);
  }
  std::sort(pds_list.begin(), pds_list.end(),
            [](const PhysDevScore& lhs, const PhysDevScore& rhs) {
              return lhs.score > rhs.score;
            });

  TEMP_LOG_INFO(kVkUtilityTag,
                std::string("physical device name: ") +
                    pds_list[0].physical_device.getProperties().deviceName);

  return pds_list[0].physical_device;
}

DeviceAndQueueFamilyIndex CreateVulkanDevice(
    const vk::PhysicalDevice& physical_device) {
  auto queue_family_properties = physical_device.getQueueFamilyProperties();

  auto gfx_queue_family_index = std::distance(
      queue_family_properties.begin(),
      std::find_if(queue_family_properties.begin(),
                   queue_family_properties.end(),
                   [](vk::QueueFamilyProperties const& qfp) {
                     return qfp.queueFlags & vk::QueueFlagBits::eGraphics;
                   }));
  TEMP_ASSERT(gfx_queue_family_index < queue_family_properties.size(), "");

  float queue_priority = 0.0f;
  vk::DeviceQueueCreateInfo queue_create_info(
      vk::DeviceQueueCreateFlags(),
      static_cast<std::uint32_t>(gfx_queue_family_index), 1, &queue_priority);

  vk::DeviceCreateInfo create_info(
      vk::DeviceCreateFlags(), 1, &queue_create_info, 0, nullptr,
      static_cast<std::uint32_t>(kDeviceExtensions.size()),
      &kDeviceExtensions[0]);

  auto device =
      physical_device.createDeviceUnique(vk::DeviceCreateInfo(create_info));

  return DeviceAndQueueFamilyIndex{
      std::move(device), static_cast<std::uint32_t>(gfx_queue_family_index)};
}

}  // namespace vulkan
}  // namespace graphics
}  // namespace temp
#endif