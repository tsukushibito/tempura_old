#pragma once
#include "temp/core/define.h"
#if defined(TEMP_PLATFORM_WINDOWS) && defined(TEMP_GRAPHICS_OPENGL)
#include "temp/graphics/opengl/gl_common.h"

namespace temp {
namespace graphics {
namespace opengl {
namespace windows {

OpenGLContextHandle CreateContext(const void* window_handle,
                                  OpenGLContextHandle shared_context = nullptr);

void DeleteContext(OpenGLContextHandle context);

void MakeCurrent(const void* window_handle, OpenGLContextHandle context);

void SwapBuffers(OpenGLContextHandle context);

OpenGLContextHandle CreateSharedContext(OpenGLContextHandle shared_context);
}  // namespace windows
}  // namespace opengl
}  // namespace graphics
}  // namespace temp
#endif