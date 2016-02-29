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

#include "temp/system/logger.h"

namespace temp {
namespace graphics {
namespace opengl {

template < class T = void >
T checkError() {
    GLenum errorCode = glGetError();
    if (errorCode == GL_NO_ERROR) {
        return;
    }

    do {
        const char *msg = "";
        switch (errorCode) {
        case GL_INVALID_ENUM:
            msg = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            msg = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            msg = "INVALID_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            msg = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            msg = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        default:
            msg = "Unknown";
            break;
        }

        system::ConsoleLogger::error("OpenGL ERROR : 0x{0:x}'{1}'\n", errorCode, msg);

        errorCode = glGetError();
    } while (errorCode != GL_NO_ERROR);
    TEMP_ASSERT(false, "OpenGL ERROR");
}

template < class T = void >
T printShaderCompileInfoLog(GLuint shader) {

    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    // if(result == GL_FALSE) debugLog("[ERROR] GLSL faled to compile.");
    if (result == GL_FALSE) system::ConsoleLogger::error("[ERROR] GLSL faled to compile.");
    GLint bufSize = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

    if (bufSize > 1) {
        std::string infoLog(bufSize, '\n');

        GLsizei length;

        /* シェーダのコンパイル時のログの内容を取得する */
        glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
        // debugLog("ShaderInfoLog:\n%s\n\n", infoLog.c_str());
        system::ConsoleLogger::error("ShaderInfoLog:\n{0}\n\n", infoLog.c_str());
    }
}

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
