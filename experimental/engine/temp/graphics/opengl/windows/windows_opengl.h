#pragma once

#include "temp/graphics/opengl/opengl_common.h"

#if defined(TEMP_PLATFORM_WINDOWS)
namespace temp {
namespace graphics {
namespace opengl {
namespace windows {

OpenGLContextHandle createContext(WindowHandle window_handle,
                                  OpenGLContextHandle shared_context = nullptr);

void deleteContext(OpenGLContextHandle context);

void makeCurrent(WindowHandle window_handle, OpenGLContextHandle context);

void swapBuffers(OpenGLContextHandle context);

OpenGLContextHandle createSharedContext(OpenGLContextHandle shared_context);
}  // namespace windows
}  // namespace opengl
}  // namespace graphics
}  // namespace temp
#endif