#include "temp/rendering/vulkan/vk_renderer.h"
#ifdef TEMP_GRAPHICS_VULKAN
#include "temp/rendering/vulkan/vk_swap_chain.h"

namespace temp {
namespace rendering {
namespace vulkan {
namespace {
const char* kVkRendererTag = "VkRenderer";
const char* kAppName = "TempuraEngine";
const char* kEngineName = "Tempura";
const std::array<const char*, 1> kValidationLayers = {
    {"VK_LAYER_LUNARG_standard_validation"}};
const std::array<const char*, 1> kExtensions = {
    {VK_EXT_DEBUG_UTILS_EXTENSION_NAME}};

VKAPI_ATTR VkBool32 VKAPI_CALL
DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
              VkDebugUtilsMessageTypeFlagsEXT messageType,
              const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
              void* pUserData) {
  if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
    TEMP_LOG_ERROR(kVkRendererTag, fmt::format("validation layer: {0}",
                                               pCallbackData->pMessage));
  } else if (messageSeverity >=
             VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
    TEMP_LOG_WARN(kVkRendererTag, fmt::format("validation layer: {0}",
                                              pCallbackData->pMessage));
  } else if (messageSeverity >=
             VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
    TEMP_LOG_TRACE(kVkRendererTag, fmt::format("validation layer: {0}",
                                               pCallbackData->pMessage));
  }

  return VK_FALSE;
}

bool IsValidationLayerSupported() {
  auto available_layers = vk::enumerateInstanceLayerProperties();

  String msg = "Supported layers:\n";
  for (auto layer_property : available_layers) {
    msg += String(layer_property.layerName) + "\n";
  }
  TEMP_LOG_INFO(kVkRendererTag, msg);

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
  create_info.enabledLayerCount = static_cast<uint32_t>(kValidationLayers.size());
  create_info.ppEnabledLayerNames = &kValidationLayers[0];
  create_info.enabledExtensionCount = static_cast<uint32_t>(kExtensions.size());
  create_info.ppEnabledExtensionNames = &kExtensions[0];

  return vk::createInstanceUnique(create_info);
}

UniqueDebugUtilsMessengerEXT CreateMessenger(
    vk::UniqueInstance& instance, vk::DispatchLoaderDynamic& loader) {
  vk::DebugUtilsMessengerCreateFlagsEXT create_flags;
  vk::DebugUtilsMessageSeverityFlagsEXT message_severity =
      vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
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

UInt32 RatePhysicalDevice(const vk::PhysicalDevice& physical_device) {
  UInt32 score = 0;

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
}  // namespace

vk::PhysicalDevice PickPhysicalDevice(const vk::UniqueInstance& instance) {
  auto physical_devices = instance->enumeratePhysicalDevices();
  TEMP_ASSERT(!physical_devices.empty(), "Not found physical devices.");

  struct PhysDevScore {
    PhysDevScore(UInt32 s, vk::PhysicalDevice& pd)
        : score(s), physical_device(pd) {}
    UInt32 score;
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

  TEMP_LOG_INFO(kVkRendererTag,
                std::string("physical device name: ") +
                    pds_list[0].physical_device.getProperties().deviceName);

  return pds_list[0].physical_device;
}

vk::UniqueDevice CreateDevice(const vk::PhysicalDevice& physical_device) {
  auto queue_family_properties = physical_device.getQueueFamilyProperties();

  size_t gfx_queue_family_index = std::distance(
      queue_family_properties.begin(),
      std::find_if(queue_family_properties.begin(),
                   queue_family_properties.end(),
                   [](vk::QueueFamilyProperties const& qfp) {
                     return qfp.queueFlags & vk::QueueFlagBits::eGraphics;
                   }));
  TEMP_ASSERT(gfx_queue_family_index < queue_family_properties.size(), "");

  float queue_priority = 0.0f;
  vk::DeviceQueueCreateInfo create_info(
      vk::DeviceQueueCreateFlags(),
      static_cast<uint32_t>(gfx_queue_family_index), 1, &queue_priority);

  return physical_device.createDeviceUnique(
      vk::DeviceCreateInfo(vk::DeviceCreateFlags(), 1, &create_info));
}

}  // namespace
VkRenderer::VkRenderer(const TaskManager::SPtr& task_manager,
                       const resource::ResourceManager::SPtr& resource_manager)
    : task_manager_(task_manager), resource_manager_(resource_manager) {
  try {
    instance_.reset(CreateInstance().release());
    dispatch_loader_dynamic_.init(*instance_);
    messenger_.reset(
        CreateMessenger(instance_, dispatch_loader_dynamic_).release());
    auto physical_device = PickPhysicalDevice(instance_);
    device_.reset(CreateDevice(physical_device).release());

  } catch (vk::SystemError err) {
    TEMP_LOG_FATAL(kVkRendererTag,
                   fmt::format("vk::SystemError: {0}", err.what()));
    exit(-1);

  } catch (...) {
    TEMP_LOG_FATAL(kVkRendererTag, "unknown error");
    exit(-1);
  }
}

void VkRenderer::Render() {}

}  // namespace vulkan
}  // namespace rendering
}  // namespace temp
#endif
