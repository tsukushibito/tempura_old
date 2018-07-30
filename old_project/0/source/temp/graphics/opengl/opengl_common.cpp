/**
 * @file opengl_common.cpp
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-22
 */

#include "temp/temp_assert.h"

#include "temp/system/logger.h"

#include "temp/graphics/opengl/opengl_common.h"

#if defined(TEMP_PLATFORM_MAC)
#include "temp/graphics/opengl/mac/opengl_mac.h"
#elif defined(TEMP_PLATFORM_WINDOWS)
#include "temp/graphics/opengl/windows/opengl_windows.h"
#elif defined(TEMP_PLATFORM_LINUX)
#endif

namespace temp {
namespace graphics {
namespace opengl {

OpenGLContextHandle createContext(WindowHandle        window_handle,
                                  OpenGLContextHandle shared_context) {
#if defined(TEMP_PLATFORM_MAC)
    return mac::createContext(window_handle, shared_context);
#elif defined(TEMP_PLATFORM_WINDOWS)
    return windows::createContext(window_handle, shared_context);
#elif defined(TEMP_PLATFORM_LINUX)
#endif
}

void deleteContext(OpenGLContextHandle context) {
#if defined(TEMP_PLATFORM_MAC)
    return mac::deleteContext(context);
#elif defined(TEMP_PLATFORM_WINDOWS)
    return windows::deleteContext(context);
#elif defined(TEMP_PLATFORM_LINUX)
#endif
}

void makeCurrent(WindowHandle window_handle, OpenGLContextHandle context) {
#if defined(TEMP_PLATFORM_MAC)
    return mac::makeCurrent(window_handle, context);
#elif defined(TEMP_PLATFORM_WINDOWS)
    return windows::makeCurrent(window_handle, context);
#elif defined(TEMP_PLATFORM_LINUX)
#endif
}

void swapBuffers(OpenGLContextHandle context) {
#if defined(TEMP_PLATFORM_MAC)
    return mac::swapBuffers(context);
#elif defined(TEMP_PLATFORM_WINDOWS)
    return windows::swapBuffers(context);
#elif defined(TEMP_PLATFORM_LINUX)
#endif
}

OpenGLContextHandle createSharedContext(OpenGLContextHandle context) {
#if defined(TEMP_PLATFORM_MAC)
    return mac::createSharedContext(context);
#elif defined(TEMP_PLATFORM_WINDOWS)
    return windows::createSharedContext(context);
#elif defined(TEMP_PLATFORM_LINUX)
#endif
}

void APIENTRY debugProc(GLenum source, GLenum type, GLuint id, GLenum severity,
                        GLsizei length, const GLchar* message,
                        const void* user_param) {
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

    temp::system::Logger::trace(ss.str().c_str());
#endif
}

void checkError() {
    GLenum errorCode = glGetError();
    if (errorCode == GL_NO_ERROR) {
        return;
    }

    do {
        const char* msg = "";
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

        system::Logger::error("OpenGL ERROR : 0x{0:x}'{1}'\n", errorCode, msg);

        errorCode = glGetError();
    } while (errorCode != GL_NO_ERROR);
    TEMP_ASSERT(false, "OpenGL ERROR");
}

void printShaderCompileInfoLog(GLuint shader) {
    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    // if(result == GL_FALSE) debugLog("[ERROR] GLSL faled to compile.");
    if (result == GL_FALSE)
        system::Logger::error("[ERROR] GLSL faled to compile.");
    GLint bufSize = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

    if (bufSize > 1) {
        std::string infoLog(bufSize, '\n');

        GLsizei length;

        /* シェーダのコンパイル時のログの内容を取得する */
        glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
        // debugLog("ShaderInfoLog:\n%s\n\n", infoLog.c_str());
        system::Logger::error("ShaderInfoLog:\n{0}\n\n", infoLog.c_str());
    }
}

void printProgramInfoLog(GLuint program) {
    GLsizei length;

    glCallWithErrorCheck(glGetProgramiv, program, GL_INFO_LOG_LENGTH, &length);
    if (length <= 1) return;

    String infoLog("", length);
    glCallWithErrorCheck(glGetProgramInfoLog, program, length, &length,
                         (GLchar*)&infoLog[0]);
    system::Logger::info("ProgramInfoLog:\n{0}\n\n", infoLog.c_str());
}

GLenum renderTargetFormatToGlFormat(RenderTargetFormat format) {
    GLenum gl_format = GL_RGBA8;

    switch (format) {
    case RenderTargetFormat::kRGBA32:
        gl_format = GL_RGBA8;
        break;
    case RenderTargetFormat::kRGBA64F:
        gl_format = GL_RGBA16F;
        break;
    case RenderTargetFormat::kRGBA128F:
        gl_format = GL_RGBA32F;
        break;
    default:
        TEMP_ASSERT(false, "invalid render target format!");
        break;
    }

    return gl_format;
}

GLenum textureFormatToGlFormat(TextureFormat format) {
    GLenum gl_format = NULL;

    switch (format) {
    case TextureFormat::kDXT1:
        gl_format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case TextureFormat::kDXT5:
        gl_format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    case TextureFormat::kRGB24:
        gl_format = GL_SRGB8;
        break;
    case TextureFormat::kAlpha8:
        gl_format = GL_R8;
        break;
    case TextureFormat::kRGBA32:
        gl_format = GL_SRGB8_ALPHA8;
        break;
    }

    return gl_format;
}

}  // namespace opengl
}  // namespace graphics
}  // namespace temp
