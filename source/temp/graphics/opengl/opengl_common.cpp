#include "temp/graphics/opengl/opengl_common.h"

#if defined TEMP_PLATFORM_WINDOWS
#define TEMP_OPENGL_EXTENSION_LINK(func, name) func name = nullptr;
#include "temp/graphics/opengl/temp_glext_link.inl"
#include "temp/graphics/opengl/temp_wglext_link.inl"
#undef TEMP_OPENGL_EXTENSION_LINK
#include "temp/graphics/opengl/windows/opengl_windows.h"
#elif defined TEMP_PLATFORM_MAC
#include "temp/graphics/opengl/mac/opengl_mac.h"
#endif

namespace temp {
namespace graphics {
namespace opengl {

OpenglContexts createContexts(void *window_handle, Size worker_thread_count) {
#if defined TEMP_PLATFORM_WINDOWS
    return windows::createContexts(static_cast< HWND >(window_handle), worker_thread_count);
#elif defined TEMP_PLATFORM_MAC
    return mac::createContexts(window_handle, worker_thread_count);
#endif
}

void deleteContexts(const OpenglContexts &contexts) {
#if defined TEMP_PLATFORM_WINDOWS
    windows::deleteContexts(contexts);
#elif defined TEMP_PLATFORM_MAC
    mac::deleteContexts(contexts);
#endif
}

void makeCurrent(void *window_handle, void *context) {
#if defined TEMP_PLATFORM_WINDOWS
    return windows::makeCurrent(static_cast< HWND >(window_handle), static_cast< HGLRC >(context));
#elif defined TEMP_PLATFORM_MAC
    return mac::makeCurrent(window_handle, context);
#endif
}

void swapBuffers(void *window_handle, void *context) {
#if defined TEMP_PLATFORM_WINDOWS
    return windows::swapBuffers(static_cast< HWND >(window_handle), static_cast< HGLRC >(context));
#elif defined TEMP_PLATFORM_MAC
    return mac::swapBuffers(window_handle, context);
#endif
}

void APIENTRY debugProc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                        const void *user_param) {

#ifndef TEMP_PLATFORM_MAC
    using namespace std;
    ostringstream ss;
    ss << "---------------------opengl-callback-start------------" << endl;
    ss << "message: " << message << endl;
    ss << "type: ";
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        ss << "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        ss << "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        ss << "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        ss << "PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        ss << "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_OTHER:
        ss << "OTHER";
        break;
    }
    ss << endl;

    ss << "id: " << id << endl;
    ss << "severity: ";
    switch (severity) {
    case GL_DEBUG_SEVERITY_LOW:
        ss << "LOW";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        ss << "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        ss << "HIGH";
        break;
    }
    ss << endl;
    ss << "source: " << source << endl;
    ss << "length: " << length << endl;
    if (user_param != nullptr) {
        ss << "user_param" << user_param << endl;
    }
    ss << "---------------------opengl-callback-end--------------" << endl;

    temp::system::ConsoleLogger::trace(ss.str().c_str());
#endif
}

void checkError() {
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
    TEMP_ASSERT(false && "OpenGL ERROR");
}

void printShaderCompileInfoLog(GLuint shader) {

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

void printProgramInfoLog(GLuint program) {
    GLsizei length;

    glCallWithErrorCheck(glGetProgramiv, program, GL_INFO_LOG_LENGTH, &length);
    if (length <= 1) return;

    String infoLog("", length);
    glCallWithErrorCheck(glGetProgramInfoLog, program, length, &length, (GLchar *)&infoLog[0]);
    system::ConsoleLogger::info("ProgramInfoLog:\n{0}\n\n", infoLog.c_str());
}

} // namespace opengl
} // namespace graphics
} // namespace temp
