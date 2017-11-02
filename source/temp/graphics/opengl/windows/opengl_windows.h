/**
 * @file opengl_windows.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-22
 */
#pragma once
#ifndef GUARD_9f089a61db6c42c59b20bab84df9afc0
#define GUARD_9f089a61db6c42c59b20bab84df9afc0

#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/windows/opengl_windows.h"

#if defined(TEMP_PLATFORM_WINDOWS)
namespace temp {
namespace graphics {
namespace opengl {
namespace windows {

OpenGLContextHandle createContext(
    WindowHandle window_handle,
    OpenGLContextHandle                shared_context = nullptr);

void deleteContext(OpenGLContextHandle context);

void makeCurrent(WindowHandle window_handle,
                 OpenGLContextHandle                context);

void swapBuffers(OpenGLContextHandle context);

OpenGLContextHandle createSharedContext(OpenGLContextHandle shared_context);
}
}
}
}

#endif

#endif  // GUARD_9f089a61db6c42c59b20bab84df9afc0
