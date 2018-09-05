#include "temp/core/define.h"
#if defined(TEMP_GRAPHICS_VULKAN)
#include "temp/graphics/vulkan/vk_device.h"
#include "temp/graphics/vulkan/vk_vertex_shader.h"

namespace temp {
namespace graphics {
namespace vulkan {

namespace {
const char* kVkVertexShader = "kVkVertexShader";

vk::UniqueShaderModule CreateShaderModule(const vk::UniqueDevice& device,
                                          const ByteData& code) {
  vk::ShaderModuleCreateInfo create_info;
  create_info.codeSize = code.size();
  create_info.pCode = reinterpret_cast<const UInt32*>(&code[0]);
  return device->createShaderModuleUnique(create_info);
}
}  // namespace

VkVertexShader::VkVertexShader(const VkDevice& device, const ByteData& code) {
  shader_module_ = CreateShaderModule(device.device(), code);
}

VkVertexShader::~VkVertexShader() {}

}  // namespace vulkan
}  // namespace graphics
}  // namespace temp

#endif