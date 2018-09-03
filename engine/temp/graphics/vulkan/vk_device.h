#pragma once
#include "temp/core/core.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include <utility>
#include <vulkan/vulkan.hpp>
#include "temp/graphics/device.h"

namespace temp {
namespace graphics {
namespace vulkan {

using UniqueDebugUtilsMessengerEXT =
    vk::UniqueHandle<vk::DebugUtilsMessengerEXT, vk::DispatchLoaderDynamic>;
using UniqueSurfaceKHR =
    vk::UniqueHandle<vk::SurfaceKHR, vk::DispatchLoaderDynamic>;

using DispatchLoaderDynamicUPtr = std::unique_ptr<vk::DispatchLoaderDynamic>;

class VkDevice : public Device, public SmartPointerType<VkDevice> {
  friend class SmartPointerType<VkDevice>;

 private:
  VkDevice(const void* default_window);

 public:
  ~VkDevice();

  SwapChainSPtr CreateSwapChain(const void* window) override;

  SwapChainSPtr default_swap_chain() override { return default_swap_chain_; }

  const vk::UniqueInstance& instance() const { return instance_; }
  const vk::PhysicalDevice& physical_device() const { return physical_device_; }
  const UInt32 queue_family_index() const { return queue_family_index_; }
  const vk::UniqueDevice& device() const { return device_; }
  const vk::DispatchLoaderDynamic& dispatch() const { return *dispatch_; }

 private:
  vk::UniqueInstance instance_;
  vk::PhysicalDevice physical_device_;
  UInt32 queue_family_index_;
  vk::UniqueDevice device_;
  UniqueDebugUtilsMessengerEXT messenger_;
  DispatchLoaderDynamicUPtr dispatch_;

  SwapChainSPtr default_swap_chain_;
};

}  // namespace vulkan
}  // namespace graphics
}  // namespace temp

#endif
