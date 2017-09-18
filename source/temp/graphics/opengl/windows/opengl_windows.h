/**
 * @file opengl_windows.h
 * @brief OpenGL Windows依存部分
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-16
 */
#pragma once
#ifndef GUARD_e399957dbea84d7d9e01b3cca35ea527
#define GUARD_e399957dbea84d7d9e01b3cca35ea527

#include "temp/graphics/opengl/opengl_define.h"

#if defined(TEMP_PLATFORM_WINDOWS)

#include "temp/graphics/opengl/opengl_device.h"
#include "temp/type.h"

namespace temp {
namespace graphics {
namespace opengl {
namespace windows {

OpenGLContextHandle createContext(
    temp::system::Window::NativeHandle window_handle,
    OpenGLContextHandle                shared_context = nullptr);

void deleteContext(OpenGLContextHandle context);

void makeCurrent(
    temp::system::Window::NativeHandle window_handle,
    OpenGLContextHandle context);

void swapBuffers(OpenGLContextHandle context);

OpenGLContextHandle createSharedContext(OpenGLContextHandle shared_context);
}
}
}
}
#endif

#endif  // GUARD_e399957dbea84d7d9e01b3cca35ea527
