/**
 * @file opengl_common.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-05-03
 */
#pragma once
#ifndef GUARD_978959c601b84191bc7b6a160046bd0b
#define GUARD_978959c601b84191bc7b6a160046bd0b

#include <utility>

#include "temp/system/window.h"

#include "temp/graphics_/graphics_common.h"
#include "temp/graphics_/opengl/opengl_define.h"

namespace temp {
namespace graphics_ {
namespace opengl {

OpenGLContextHandle createContext(
    temp::system::Window::NativeHandle window_handle,
    OpenGLContextHandle                shared_context = nullptr);

void deleteContext(OpenGLContextHandle context);

void makeCurrent(
    temp::system::Window::NativeHandle window_handle,
    OpenGLContextHandle                context);

void swapBuffers(OpenGLContextHandle context);

OpenGLContextHandle createSharedContext(OpenGLContextHandle shared_context);

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
                                                    std::forward<Args>(
                                                        args)...);
}

GLenum renderTargetFormatToGlFormat(RenderTargetFormat format);

GLenum textureFormatToGlFormat(TextureFormat format);

}  // namespace opengl
}  // namespace graphics
}  // namespace temp
#endif  // GUARD_978959c601b84191bc7b6a160046bd0b
