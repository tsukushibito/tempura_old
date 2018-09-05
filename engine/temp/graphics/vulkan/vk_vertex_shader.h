#pragma once
#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include <vulkan/vulkan.hpp>
#include "temp/core/core.h"
#include "temp/graphics/vertex_shader.h"

namespace temp {
namespace graphics {
namespace vulkan {

class VkDevice;

class VkVertexShader : public VertexShader,
                       public SmartPointerType<VkVertexShader> {
  friend class SmartPointerType<VkVertexShader>;

 private:
  VkVertexShader(const VkDevice& device, const ByteData& code);

 public:
  ~VkVertexShader();

  GraphicsApi graphics_api() const override { return GraphicsApi::kVulkan; }

  vk::UniqueShaderModule shader_module_;
};
}  // namespace vulkan
}  // namespace graphics
}  // namespace temp

#endif
