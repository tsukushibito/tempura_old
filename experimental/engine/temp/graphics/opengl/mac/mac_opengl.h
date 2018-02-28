#pragma once
#include "temp/graphics/opengl/opengl_common.h"
#if defined(TEMP_PLATFORM_MAC)

namespace temp {
namespace graphics {
namespace opengl {
namespace mac {

OpenGLContextHandle createContext(WindowHandle window_handle,
                                  OpenGLContextHandle shared_context = nullptr);

void deleteContext(OpenGLContextHandle context);

void makeCurrent(WindowHandle window_handle, OpenGLContextHandle context);

void swapBuffers(OpenGLContextHandle context);

OpenGLContextHandle createSharedContext(OpenGLContextHandle shared_context);
}  // namespace mac
}  // namespace opengl
}  // namespace graphics
}  // namespace temp
#endif