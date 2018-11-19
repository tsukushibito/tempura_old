#include "temp/core/define.h"
#ifdef TEMP_GRAPHICS_VULKAN
#include <new>
#include <string>
#include "temp/core/core.h"
#include "temp/graphics/vulkan/vk_device.h"
#include "temp/graphics/vulkan/vk_fragment_shader.h"
#include "temp/graphics/vulkan/vk_swap_chain.h"
#include "temp/graphics/vulkan/vk_vertex_shader.h"

namespace temp {
namespace graphics {
namespace vulkan {

namespace {
const char* kVkDeviceTag = "VkDevice";
}

VkDevice::VkDevice(const void* default_window) {
  try {
    instance_ = CreateInstance();
    physical_device_ = PickPhysicalDevice(instance_);
    auto device_and_queue_family_index = CreateVulkanDevice(physical_device_);
    device_ = std::move(device_and_queue_family_index.device);
    queue_family_indices_.graphics_family =
        device_and_queue_family_index.queue_family_index;
    dispatch_ = DispatchLoaderDynamicUPtr(new vk::DispatchLoaderDynamic());
    dispatch_->init(*instance_, *device_);
    messenger_ = CreateMessenger(instance_, *dispatch_);

    default_swap_chain_ = CreateSwapChain(default_window);

  } catch (vk::SystemError err) {
    TEMP_LOG_FATAL(kVkDeviceTag,
                   fmt::format("vk::SystemError: {0}", err.what()));
    exit(-1);

  } catch (...) {
    TEMP_LOG_FATAL(kVkDeviceTag, "unknown error");
    exit(-1);
  }
}

VkDevice::~VkDevice() {
  default_swap_chain_.reset();

  messenger_.reset(nullptr);
  dispatch_.reset(nullptr);
  device_.reset(nullptr);
  instance_.reset(nullptr);
}

SwapChainSPtr VkDevice::CreateSwapChain(const void* window) const {
  return VkSwapChain::MakeShared(*this, window);
}

VertexShaderSPtr VkDevice::CreateVertexShader(const ByteData& byte_data) const {
  return VkVertexShader::MakeShared(*this, byte_data);
}

FragmentShaderSPtr VkDevice::CreateFragmentShader(
    const ByteData& byte_data) const {
  return VkFragmentShader::MakeShared(*this, byte_data);
}

}  // namespace vulkan
}  // namespace graphics
}  // namespace temp
#endif
