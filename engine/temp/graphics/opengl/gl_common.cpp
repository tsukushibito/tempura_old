#include "temp/graphics/opengl/gl_common.h"
#if defined(TEMP_GRAPHICS_OPENGL)
#include "temp/core/core.h"

#if defined(TEMP_PLATFORM_MAC)
#include "temp/graphics/opengl/mac/mac_opengl.h"
#elif defined(TEMP_PLATFORM_WINDOWS)
#include "temp/graphics/opengl/windows/gl_windows.h"
#elif defined(TEMP_PLATFORM_LINUX)
#endif

#if defined(TEMP_PLATFORM_WINDOWS) || defined(TEMP_PLATFORM_LINUX)
#define TEMP_OPENGL_EXTENSION_LINK(func, name) func name;
#include "temp/graphics/opengl/gl_ext/temp_glext_link.inl"
#if defined(TEMP_PLATFORM_LINUX)
#elif defined(TEMP_PLATFORM_WINDOWS)
#include "temp/graphics/opengl/gl_ext/temp_wglext_link.inl"
#endif
#undef TEMP_OPENGL_EXTENSION_LINK
#endif

namespace temp {
namespace graphics {
namespace opengl {
namespace {
const char* kOpenGLTag = "OpenGL";
}

OpenGLContextHandle CreateContext(const void* window,
                                  OpenGLContextHandle shared_context) {
#if defined(TEMP_PLATFORM_MAC)
  return mac::CreateContext(window, shared_context);
#elif defined(TEMP_PLATFORM_WINDOWS)
  return windows::CreateContext(window, shared_context);
#elif defined(TEMP_PLATFORM_LINUX)
#endif
}

void DeleteContext(OpenGLContextHandle context) {
#if defined(TEMP_PLATFORM_MAC)
  return mac::DeleteContext(context);
#elif defined(TEMP_PLATFORM_WINDOWS)
  return windows::DeleteContext(context);
#elif defined(TEMP_PLATFORM_LINUX)
#endif
}

void MakeCurrent(const void* window, OpenGLContextHandle context) {
#if defined(TEMP_PLATFORM_MAC)
  return mac::MakeCurrent(window_handle, context);
#elif defined(TEMP_PLATFORM_WINDOWS)
  return windows::MakeCurrent(window, context);
#elif defined(TEMP_PLATFORM_LINUX)
#endif
}

void SwapBuffers(OpenGLContextHandle context) {
#if defined(TEMP_PLATFORM_MAC)
  return mac::SwapBuffers(context);
#elif defined(TEMP_PLATFORM_WINDOWS)
  return windows::SwapBuffers(context);
#elif defined(TEMP_PLATFORM_LINUX)
#endif
}

OpenGLContextHandle CreateSharedContext(OpenGLContextHandle context) {
#if defined(TEMP_PLATFORM_MAC)
  return mac::CreateSharedContext(context);
#elif defined(TEMP_PLATFORM_WINDOWS)
  return windows::CreateSharedContext(context);
#elif defined(TEMP_PLATFORM_LINUX)
#endif
}

void APIENTRY DebugProc(GLenum source, GLenum type, GLuint id, GLenum severity,
                        GLsizei length, const GLchar* message,
                        const void* user_param) {
#ifndef TEMP_PLATFORM_MAC
  using namespace std;
  StringStream ss;
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

  TEMP_LOG_DEBUG(kOpenGLTag, ss.str());
#endif
}

void CheckError() {
  GLenum error_code = glGetError();
  if (error_code == GL_NO_ERROR) {
    return;
  }

  do {
    const char* msg = "";
    switch (error_code) {
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

    StringStream ss;
    ss << "0x" << std::hex << error_code << ": " << msg;
    TEMP_LOG_ERROR(kOpenGLTag, ss.str());

    error_code = glGetError();
  } while (error_code != GL_NO_ERROR);
  TEMP_ASSERT(false, "OpenGL ERROR");
}

void PrintShaderCompileInfoLog(GLuint shader) {
  GLint result;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  // if(result == GL_FALSE) debugLog("[ERROR] GLSL faled to compile.");
  if (result == GL_FALSE) {
    TEMP_LOG_ERROR(kOpenGLTag, "GLSL faled to compile.");
  }
  GLint buf_size = 0;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &buf_size);

  if (buf_size > 1) {
    String infoLog(buf_size, '\n');

    GLsizei length;

    /* シェーダのコンパイル時のログの内容を取得する */
    glGetShaderInfoLog(shader, buf_size, &length, &infoLog[0]);
    StringStream ss;
    ss << "ShaderInfoLog:" << std::endl;
    ss << infoLog << std::endl;
    TEMP_LOG_INFO(kOpenGLTag, ss.str());
  }
}

void PrintProgramInfoLog(GLuint program) {
  GLsizei length;

  glCallWithErrorCheck(glGetProgramiv, program, GL_INFO_LOG_LENGTH, &length);
  if (length <= 1) return;

  String infoLog("", length);
  glCallWithErrorCheck(glGetProgramInfoLog, program, length, &length,
                       (GLchar*)&infoLog[0]);
  StringStream ss;
  ss << "ProgramInfoLog:" << std::endl;
  ss << infoLog << std::endl;
  TEMP_LOG_INFO(kOpenGLTag, ss.str());
}

GLenum RenderTargetFormatToGlFormat(RenderTargetFormat format) {
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

GLenum TextureFormatToGlFormat(TextureFormat format) {
  GLenum gl_format = NULL;

  switch (format) {
    case TextureFormat::kRGBX32:
      gl_format = GL_SRGB8_ALPHA8;
      break;
    case TextureFormat::kRGBA32:
      gl_format = GL_SRGB8_ALPHA8;
      break;
    case TextureFormat::kAlpha8:
      gl_format = GL_R8;
      break;
    case TextureFormat::kBC1:
      gl_format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
      break;
    case TextureFormat::kBC3:
      gl_format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
      break;
    case TextureFormat::kBC7:
      // TODO:
      break;
  }

  return gl_format;
}

}  // namespace opengl
}  // namespace graphics
}  // namespace temp

#endif