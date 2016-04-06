﻿/**
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

#ifndef TEMP_PLATFORM_MAC
#ifdef TEMP_USE_GLEW
#include <GL/glew.h>
#if defined TEMP_PLATFORM_LINUX
#include <GL/glxew.h>
#elif defined TEMP_PLATFORM_WINDOWS
#include <GL/wglew.h>
#endif
#else   // #ifdef TEMP_USE_GLEW
#include <GL/gl.h>
#include <GL/glu.h>
#include <gl_ext/glext.h>
// #include <gl_ext/glcorearb.h>
#define TEMP_OPENGL_EXTENSION_LINK(func, name) extern func name;
#include "temp/graphics/opengl/temp_glext_link.inl"
// #include "temp/graphics/opengl/temp_glcorearb_link.inl"
#ifdef TEMP_PLATFORM_LINUX
#include <gl_ext/glxext.h>
#elif defined TEMP_PLATFORM_WINDOWS
#include <gl_ext/wglext.h>
#include "temp/graphics/opengl/temp_wglext_link.inl"
#endif
#undef TEMP_OPENGL_EXTENSION_LINK
#endif  // #ifdef TEMP_USE_GLEW
#else
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif  // #ifndef TEMP_PLATFORM_MAC

#include "temp/container.h"
#include "temp/temp_assert.h"
#include "temp/system/logger.h"

namespace temp {
namespace graphics {
namespace opengl {

struct OpenglCommand {
};

struct OpenglContexts {
    void *context_for_application_thread;   // アプリ実行スレッド用
    void *context_for_main_thread;          // ゲームメインスレッド用
    void *context_for_render_thread;
    void *context_for_load_thread;
    Vector<void*> contexts_for_worker_thread;
};

OpenglContexts createContexts(void *window_handle, Size worker_thread_count);
void deleteContexts(const OpenglContexts &contexts);

void makeCurrent(void *window_handle, void *context);

void swapBuffers(void *window_handle, void *context);

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
void APIENTRY
debugProc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *user_param);


void checkError();

void printShaderCompileInfoLog(GLuint shader);

void printProgramInfoLog(GLuint program);

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
