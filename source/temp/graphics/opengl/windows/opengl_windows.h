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

#include "temp/define.h"

#if defined(TEMP_PLATFORM_WINDOWS)
#include <Windows.h>

#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl_ext/wglext.h>
#include <gl_ext/glext.h>
#define TEMP_OPENGL_EXTENSION_LINK(func, name) extern func name;
#include <gl_ext/temp_glext_link.inl>
#include <gl_ext/temp_wglext_link.inl>
#undef TEMP_OPENGL_EXTENSION_LINK

#include "temp/graphics/opengl/opengl_device.h"
#include "temp/type.h"

namespace temp {
namespace graphics {
namespace opengl {
namespace windows {

DeviceHandle createContext(const temp::system::WindowHandle& window_handle);

void deleteContext(HGLRC context);

void makeCurrent(HGLRC context);

void swapBuffers(HGLRC context);

void* deviceHandleToNsOpenGlContext(const DeviceHandle& handle);

}
}
}
}
#endif

#endif // GUARD_e399957dbea84d7d9e01b3cca35ea527
