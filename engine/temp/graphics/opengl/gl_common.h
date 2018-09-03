#pragma once

#include "temp/core/core.h"
#if defined(TEMP_GRAPHICS_OPENGL)
#include "temp/graphics/graphics_common.h"

#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#if defined(TEMP_PLATFORM_WINDOWS) || defined(TEMP_PLATFORM_LINUX)
#include <GL/gl.h>
#include <GL/glu.h>
#include "temp/graphics/opengl/gl_ext/glext.h"

#define TEMP_OPENGL_EXTENSION_LINK(func, name) extern func name;
#include "temp/graphics/opengl/gl_ext/temp_glext_link.inl"
#if defined(TEMP_PLATFORM_LINUX)
#include <gl_ext/glxext.h>
#elif defined(TEMP_PLATFORM_WINDOWS)
#include "temp/graphics/opengl/gl_ext/wglext.h"
#include "temp/graphics/opengl/gl_ext/temp_wglext_link.inl"
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

OpenGLContextHandle CreateContext(const void* window,
                                  OpenGLContextHandle shared_context = nullptr);

void DeleteContext(OpenGLContextHandle context);

void MakeCurrent(const void* window, OpenGLContextHandle context);

void SwapBuffers(OpenGLContextHandle context);

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
void APIENTRY DebugProc(GLenum source, GLenum type, GLuint id, GLenum severity,
                        GLsizei length, const GLchar* message,
                        const void* user_param);

void CheckError();

void PrintShaderCompileInfoLog(GLuint shader);

void PrintProgramInfoLog(GLuint program);

template <typename ReturnType, typename F, typename... Args>
struct glCallWithErrorCheck_Impl {
  static ReturnType call(F&& function, Args&&... args) {
    ReturnType result = function(args...);
#ifndef TEMP_OPENGL_WITHOUT_CHECK_ERROR
    CheckError();
#endif
    return std::move(result);
  }
};

template <typename F, typename... Args>
struct glCallWithErrorCheck_Impl<void, F, Args...> {
  static void call(F&& function, Args&&... args) {
    function(args...);
#ifndef TEMP_OPENGL_WITHOUT_CHECK_ERROR
    CheckError();
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

GLenum RenderTargetFormatToGlFormat(RenderTargetFormat format);

GLenum TextureFormatToGlFormat(TextureFormat format);
}  // namespace opengl
}  // namespace graphics
}  // namespace temp
#endif