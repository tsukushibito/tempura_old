/**
 * @file opengl_common.h
 * @brief opengl utility
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-28
 */
#pragma once
#ifndef GUARD_30a587128c704bc6afdf3171ce02ce8c
#define GUARD_30a587128c704bc6afdf3171ce02ce8c

#include "temp/define.h"

#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#include <GL/glew.h>
#if defined TEMP_PLATFORM_LINUX
#include <GL/glxew.h>
#elif defined TEMP_PLATFORM_WINDOWS
#include <GL/wglew.h>
#endif

#include "temp/temp_assert.h"
#include "temp/system/logger.h"

namespace temp {
namespace graphics {
namespace opengl {

struct OpenglContexts {
	void *context_for_render;
	void *context_for_load;
};

OpenglContexts createContext(void *window_handle);

void makeCurrent(void *window_handle, void *context);

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
void GLAPIENTRY
debugProc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *user_param);


void checkError();

void printShaderCompileInfoLog(GLuint shader);

template < typename ReturnType, typename F, typename... Args >
struct glCallWithErrorCheck_Impl {
    static ReturnType call(F &&function, Args &&... args) {
        ReturnType result = function(args...);
#ifndef TEMP_OPENGL_WITHOUT_CHECK_ERROR
        checkError();
#endif
        return std::move(result);
    }
};

template < typename F, typename... Args >
struct glCallWithErrorCheck_Impl< void, F, Args... > {
    static void call(F &&function, Args &&... args) {
        function(args...);
#ifndef TEMP_OPENGL_WITHOUT_CHECK_ERROR
        checkError();
#endif
    }
};

template < typename F, typename... Args >
auto glCallWithErrorCheck(F &&function, Args &&... args) -> decltype(function(args...)) {
    return glCallWithErrorCheck_Impl< decltype(function(args...)), F, Args... >::call(std::forward< F >(function),
                                                                                      std::forward< Args >(args)...);
}

} // namespace opengl
} // namespace graphics
} // namespace temp

#endif // GUARD_30a587128c704bc6afdf3171ce02ce8c
