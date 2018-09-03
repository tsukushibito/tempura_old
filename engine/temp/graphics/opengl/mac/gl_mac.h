#pragma once
#include "temp/core/core.h"
#if defined(TEMP_PLATFORM_MAC)
#include "temp/graphics/opengl/gl_common.h"

namespace temp {
namespace graphics {
namespace opengl {
namespace mac {

OpenGLContextHandle CreateContext(const void* window,
                                  OpenGLContextHandle shared_context = nullptr);

void DeleteContext(OpenGLContextHandle context);

void MakeCurrent(const void* window, OpenGLContextHandle context);

void SwapBuffers(OpenGLContextHandle context);

OpenGLContextHandle CreateSharedContext(OpenGLContextHandle shared_context);
}  // namespace mac
}  // namespace opengl
}  // namespace graphics
}  // namespace temp
#endif