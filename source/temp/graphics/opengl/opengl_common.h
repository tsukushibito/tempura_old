#pragma once

#include "temp/common/define.h"
#include "temp/graphics/graphics.h"

#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#if defined(TEMP_PLATFORM_WINDOWS) || defined(TEMP_PLATFORM_LINUX)
#include <GL/gl.h>
#include <GL/glu.h>
#include <gl_ext/glext.h>

#define TEMP_OPENGL_EXTENSION_LINK(func, name) extern func name;
#include <gl_ext/temp_glext_link.inl>
#if defined(TEMP_PLATFORM_LINUX)
#include <gl_ext/glxext.h>
#elif defined(TEMP_PLATFORM_WINDOWS)
#include <gl_ext/wglext.h>
#include <gl_ext/temp_wglext_link.inl>
#endif
#undef TEMP_OPENGL_EXTENSION_LINK

#else
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif  // defined(TEMP_PLATFORM_WINDOWS) || defined(TEMP_PLATFORM_LINUX)

namespace temp {
namespace graphics {
namespace opengl {

#if defined(TEMP_PLATFORM_MAC)
using OpenGLContextHandle = void*;
#elif defined(TEMP_PLATFORM_WINDOWS)
using OpenGLContextHandle = HGLRC;
#endif

OpenGLContextHandle createContext(WindowHandle window_handle,
                                  OpenGLContextHandle shared_context = nullptr);

void deleteContext(OpenGLContextHandle context);

void makeCurrent(WindowHandle window_handle, OpenGLContextHandle context);

void swapBuffers(OpenGLContextHandle context);

/**
 * @brief OpenGL デバッグプロシージャ
 *
 * @param source
 * @param type
 * @param id
 * @param severity
 * @param length
 * @param message
 * @param user_param
 *
 * @return
 */
void APIENTRY debugProc(GLenum source, GLenum type, GLuint id, GLenum severity,
                        GLsizei length, const GLchar* message,
                        const void* user_param);

void checkError();

void printShaderCompileInfoLog(GLuint shader);

void printProgramInfoLog(GLuint program);

template <typename ReturnType, typename F, typename... Args>
struct glCallWithErrorCheck_Impl {
  static ReturnType call(F&& function, Args&&... args) {
    ReturnType result = function(args...);
#ifndef TEMP_OPENGL_WITHOUT_CHECK_ERROR
    checkError();
#endif
    return std::move(result);
  }
};

template <typename F, typename... Args>
struct glCallWithErrorCheck_Impl<void, F, Args...> {
  static void call(F&& function, Args&&... args) {
    function(args...);
#ifndef TEMP_OPENGL_WITHOUT_CHECK_ERROR
    checkError();
#endif
  }
};

template <typename F, typename... Args>
auto glCallWithErrorCheck(F&& function, Args&&... args)
    -> decltype(function(args...)) {
  return glCallWithErrorCheck_Impl<decltype(function(args...)), F,
                                   Args...>::call(std::forward<F>(function),
                                                  std::forward<Args>(args)...);
}

GLenum renderTargetFormatToGlFormat(RenderTargetFormat format);

GLenum textureFormatToGlFormat(TextureFormat format);
}
}  // namespace graphics
}  // namespace temp