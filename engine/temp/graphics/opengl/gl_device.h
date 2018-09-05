#pragma once
#include "temp/core/core.h"
#if defined(TEMP_GRAPHICS_OPENGL)
#include "temp/graphics/device.h"
#include "temp/graphics/opengl/gl_common.h"

namespace temp {
namespace graphics {
namespace opengl {

class GlDevice : public Device, public SmartPointerType<GlDevice> {
  friend class SmartPointerType<GlDevice>;

 private:
  GlDevice(const void* default_window);

 public:
  ~GlDevice();

  SwapChainSPtr CreateSwapChain(const void* window) const override;

  SwapChainSPtr default_swap_chain() const override;

  GraphicsApi graphics_api() const override { return GraphicsApi::kOpenGl; }

 private:
  OpenGLContextHandle context_;
};

}  // namespace opengl
}  // namespace graphics
}  // namespace temp

#endif
