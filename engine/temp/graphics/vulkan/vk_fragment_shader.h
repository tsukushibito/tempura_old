#pragma once
#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include <vulkan/vulkan.hpp>
#include "temp/core/core.h"
#include "temp/graphics/fragment_shader.h"

namespace temp {
namespace graphics {
namespace vulkan {

class VkDevice;

class VkFragmentShader : public FragmentShader,
                         public SmartPointerType<VkFragmentShader> {
  friend class SmartPointerType<VkFragmentShader>;

 private:
  VkFragmentShader(const VkDevice& device, const ByteData& code);

 public:
  ~VkFragmentShader();

  GraphicsApi graphics_api() const override { return GraphicsApi::kVulkan; }

  vk::UniqueShaderModule shader_module_;
  vk::PipelineShaderStageCreateInfo shader_stage_;
};
}  // namespace vulkan
}  // namespace graphics
}  // namespace temp

#endif
