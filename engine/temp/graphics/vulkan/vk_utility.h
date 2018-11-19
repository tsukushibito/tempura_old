#pragma once
#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include <vulkan/vulkan.hpp>

#include "temp/core/type.h"

namespace temp {
namespace graphics {
namespace vulkan {

using UniqueDebugUtilsMessengerEXT =
    vk::UniqueHandle<vk::DebugUtilsMessengerEXT, vk::DispatchLoaderDynamic>;
using UniqueSurfaceKHR =
    vk::UniqueHandle<vk::SurfaceKHR, vk::DispatchLoaderDynamic>;

using DispatchLoaderDynamicUPtr = std::unique_ptr<vk::DispatchLoaderDynamic>;

struct QueueFamilyIndices {
  std::uint32_t graphics_family = (std::uint32_t)-1;
  std::uint32_t present_family = (std::uint32_t)-1;
};

struct DeviceAndQueueFamilyIndex {
  vk::UniqueDevice device;
  std::uint32_t queue_family_index;
};

VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

bool IsValidationLayerSupported();

vk::UniqueInstance CreateInstance();

UniqueDebugUtilsMessengerEXT CreateMessenger(
    vk::UniqueInstance& instance, const vk::DispatchLoaderDynamic& loader);

std::uint32_t RatePhysicalDevice(const vk::PhysicalDevice& physical_device);

vk::PhysicalDevice PickPhysicalDevice(const vk::UniqueInstance& instance);

DeviceAndQueueFamilyIndex CreateVulkanDevice(
    const vk::PhysicalDevice& physical_device);
}  // namespace vulkan
}  // namespace graphics
}  // namespace temp

#endif