#include "temp/graphics/opengl/gl_device.h"
#if defined(TEMP_GRAPHICS_OPENGL)
namespace temp {
namespace graphics {
namespace opengl {
GlDevice::GlDevice(const void* default_window) {
  context_ = CreateContext(default_window, nullptr);
}

GlDevice::~GlDevice() { DeleteContext(context_); }

SwapChainSPtr GlDevice::CreateSwapChain(const void* window) const {
  return nullptr;
}

VertexShaderSPtr GlDevice::CreateVertexShader(const ByteData& byte_data) const {
  return nullptr;
}

FragmentShaderSPtr GlDevice::CreateFragmentShader(
    const ByteData& byte_data) const {
  return nullptr;
}

SwapChainSPtr GlDevice::default_swap_chain() const { return nullptr; }
}  // namespace opengl
}  // namespace graphics
}  // namespace temp
#endif