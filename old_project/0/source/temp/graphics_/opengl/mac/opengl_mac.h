/**
 * @file opengl_mac.h
 * @brief OpenGL OSX依存部分
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-01
 */
#pragma once
#ifndef GUARD_f46e2e02182b48f1bdc18d05b9fc86fa
#define GUARD_f46e2e02182b48f1bdc18d05b9fc86fa

#include "temp/graphics_/opengl/opengl_define.h"

#ifdef TEMP_PLATFORM_MAC

#include "temp/graphics_/opengl/opengl_device.h"
#include "temp/type.h"

namespace temp {
namespace graphics_ {
namespace opengl {
namespace mac {

OpenGLContextHandle createContext(
    temp::system::Window::NativeHandle window_handle,
    OpenGLContextHandle                shared_context = nullptr);

void deleteContext(OpenGLContextHandle context);

void makeCurrent(temp::system::Window::NativeHandle window_handle,
                 OpenGLContextHandle                context);

void swapBuffers(OpenGLContextHandle context);

OpenGLContextHandle createSharedContext(OpenGLContextHandle shared_context);
}
}
}
}
#endif  // TEMP_PLATFORM_MAC
#endif  // GUARD_f46e2e02182b48f1bdc18d05b9fc86fa
