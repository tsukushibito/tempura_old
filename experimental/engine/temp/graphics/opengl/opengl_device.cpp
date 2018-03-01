#include "temp/graphics/opengl/opengl_device.h"
#include "temp/core/logger.h"
#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics {
namespace opengl {

namespace {
const Char* kOpenGLDeviceTag = "OpenGLDevice";
}

Device::SPtr OpenGLDevice::create(WindowHandle window_handle,
                                  const core::ThreadPool::SPtr& render_thread,
                                  const core::ThreadPool::SPtr& load_thread) {
  struct Creator : public OpenGLDevice {
    Creator(WindowHandle window_handle,
            const core::ThreadPool::SPtr& render_thread,
            const core::ThreadPool::SPtr& load_thread)
        : OpenGLDevice(window_handle, render_thread, load_thread) {}
  };

  return std::make_shared<Creator>(window_handle, render_thread, load_thread);
}

OpenGLDevice::OpenGLDevice(WindowHandle window_handle,
                           const core::ThreadPool::SPtr& render_thread,
                           const core::ThreadPool::SPtr& load_thread)
    : window_handle_(window_handle),
      render_thread_(render_thread),
      load_thread_(load_thread) {
  // 各スレッド用コンテキストを作成
  render_context_ = createContext(window_handle_, nullptr);
  load_context_ = createContext(window_handle_, render_context_);

  {
    auto future = render_thread_->pushTask(
        0, [this]() { makeCurrent(window_handle_, render_context_); });
    future.wait();
  }

  {
    auto future = load_thread_->pushTask(
        0, [this]() { makeCurrent(window_handle_, load_context_); });
    future.wait();
  }
}

OpenGLDevice::~OpenGLDevice() {
  deleteContext(render_context_);
  deleteContext(load_context_);
}

RenderTargetSPtr OpenGLDevice::createRenderTarget(
    const RenderTargetDesc& desc) {
  using temp::core::Logger;

  auto task = [this, &desc]() {
    GLuint id;
    glCallWithErrorCheck(glGenTextures, 1, &id);
    glCallWithErrorCheck(glBindTexture, GL_TEXTURE_2D, id);

    auto gl_format = renderTargetFormatToGlFormat(desc.format);
    GLenum gl_type = desc.format == RenderTargetFormat::kRGBA32
                         ? GL_UNSIGNED_BYTE
                         : GL_FLOAT;
    glCallWithErrorCheck(glTexImage2D, GL_TEXTURE_2D, 0, gl_format,
                         (GLsizei)desc.width, (GLsizei)desc.height, 0, GL_RGBA,
                         gl_type, nullptr);

    glCallWithErrorCheck(glBindTexture, GL_TEXTURE_2D, 0);
    return id;
  };

  GLuint id = execInLoadThread(task);
  StringStream ss;
  ss << "render_target has created. id: " << id;
  Logger::trace(kOpenGLDeviceTag, ss.str());

  struct Creator : OpenGLRenderTarget {
    Creator(GLuint id, const RenderTargetDesc& desc,
            std::function<void(GLuint)> on_destroy)
        : OpenGLRenderTarget(id, desc, on_destroy) {}
  };

  return std::make_shared<Creator>(id, desc, [this](GLuint id) {
    auto task = [id]() { glCallWithErrorCheck(glDeleteTextures, 1, &id); };
    execInLoadThread(task);
    StringStream ss;
    ss << "render_target has deleted. id: " << id;
    Logger::trace(kOpenGLDeviceTag, ss.str());
  });
}

TextureSPtr OpenGLDevice::createTexture(const TextureDesc& desc,
                                        const void* data) {
  using temp::core::Logger;

  auto task = [this, &desc, data]() {
    GLuint id;
    glCallWithErrorCheck(glGenTextures, 1, &id);
    glCallWithErrorCheck(glBindTexture, GL_TEXTURE_2D, id);

    auto gl_internal_format = textureFormatToGlFormat(desc.format);
    GLenum gl_type = GL_UNSIGNED_BYTE;
    GLenum gl_format;
    Size size = 0;
    switch (desc.format) {
      case TextureFormat::kDXT1:
        size = ((desc.width + 3) / 4) * ((desc.height + 3) / 4) * 8;
        break;
      case TextureFormat::kDXT5:
        size = ((desc.width + 3) / 4) * ((desc.height + 3) / 4) * 16;
        break;
      case TextureFormat::kRGB24:
        gl_format = GL_RGB;
        break;
      case TextureFormat::kAlpha8:
        gl_format = GL_RED;
        break;
      case TextureFormat::kRGBA32:
        gl_format = GL_RGBA;
        break;
    }

    if (desc.format == TextureFormat::kDXT1 ||
        desc.format == TextureFormat::kDXT5) {
      glCallWithErrorCheck(glCompressedTexImage2D, GL_TEXTURE_2D, 0,
                           gl_internal_format, (GLsizei)desc.width,
                           (GLsizei)desc.height, 0, (GLsizei)size, data);
    } else {
      glCallWithErrorCheck(glTexImage2D, GL_TEXTURE_2D, 0, gl_internal_format,
                           (GLsizei)desc.width, (GLsizei)desc.height, 0,
                           gl_format, gl_type, data);
    }

    glCallWithErrorCheck(glBindTexture, GL_TEXTURE_2D, 0);
    return id;
  };

  GLuint id = execInLoadThread(task);
  StringStream ss;
  ss << "texture has created. id: " << id;
  Logger::trace(kOpenGLDeviceTag, ss.str());

  struct Creator : OpenGLTexture {
    Creator(GLuint id, const TextureDesc& desc,
            std::function<void(GLuint)> on_destroy)
        : OpenGLTexture(id, desc, on_destroy) {}
  };

  return std::make_shared<Creator>(id, desc, [this](GLuint id) {
    auto task = [id]() { glCallWithErrorCheck(glDeleteTextures, 1, &id); };
    execInLoadThread(task);
    StringStream ss;
    ss << "texture has deleted. id: " << id;
    Logger::trace(kOpenGLDeviceTag, ss.str());
  });
}

VertexBufferSPtr OpenGLDevice::createVertexBuffer(const VertexBufferDesc& desc,
                                                  const void* data) {
  using temp::core::Logger;

  auto task = [this, desc, data]() {
    GLuint id;
    glCallWithErrorCheck(glGenBuffers, 1, &id);
    glCallWithErrorCheck(glBindBuffer, GL_ARRAY_BUFFER, id);
    glCallWithErrorCheck(glBufferData, GL_ARRAY_BUFFER,
                         static_cast<GLsizei>(desc.size), data, GL_STATIC_DRAW);
    glCallWithErrorCheck(glBindBuffer, GL_ARRAY_BUFFER, 0);
    return id;
  };

  GLuint id = execInLoadThread(task);
  StringStream ss;
  ss << "vertex buffer has created. id: " << id;
  Logger::trace(kOpenGLDeviceTag, ss.str());

  struct Creator : OpenGLVertexBuffer {
    Creator(GLuint id, const VertexBufferDesc& desc,
            std::function<void(GLuint)> on_destroy)
        : OpenGLVertexBuffer(id, desc, on_destroy) {}
  };

  return std::make_shared<Creator>(id, desc, [this](GLuint id) {
    auto task = [id]() { glCallWithErrorCheck(glDeleteBuffers, 1, &id); };
    execInLoadThread(task);
    StringStream ss;
    ss << "vertex buffer has deleted. id: " << id;
    Logger::trace(kOpenGLDeviceTag, ss.str());
  });
}

IndexBufferSPtr OpenGLDevice::createIndexBuffer(const IndexBufferDesc& desc,
                                                const void* data) {
  using temp::core::Logger;

  auto task = [this, desc, data]() {
    GLuint id;
    glCallWithErrorCheck(glGenBuffers, 1, &id);
    glCallWithErrorCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, id);
    glCallWithErrorCheck(glBufferData, GL_ELEMENT_ARRAY_BUFFER,
                         static_cast<GLsizei>(desc.size), data, GL_STATIC_DRAW);
    glCallWithErrorCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);
    return id;
  };

  GLuint id = execInLoadThread(task);
  StringStream ss;
  ss << "index buffer has created. id: " << id;
  Logger::trace(kOpenGLDeviceTag, ss.str());

  struct Creator : OpenGLIndexBuffer {
    Creator(GLuint id, const IndexBufferDesc& desc,
            std::function<void(GLuint)> on_destroy)
        : OpenGLIndexBuffer(id, desc, on_destroy) {}
  };

  return std::make_shared<Creator>(id, desc, [this](GLuint id) {
    auto task = [id]() { glCallWithErrorCheck(glDeleteBuffers, 1, &id); };
    execInLoadThread(task);
    StringStream ss;
    ss << "index buffer has deleted. id: " << id;
    Logger::trace(kOpenGLDeviceTag, ss.str());
  });
}

PixelShaderSPtr OpenGLDevice::createPixelShader(const ShaderCode& code) {
  using temp::core::Logger;

  auto task = [this, code]() {
    GLuint id = glCallWithErrorCheck(glCreateShader, GL_FRAGMENT_SHADER);
    if (!code.is_binary_) {
      const GLchar* p_code = code.code_.c_str();
      GLint length = static_cast<GLint>(code.code_.size());
      glCallWithErrorCheck(glShaderSource, id, 1, &p_code, &length);
      glCallWithErrorCheck(glCompileShader, id);
      printShaderCompileInfoLog(id);
    } else {
    }

    return id;
  };

  GLuint id = execInLoadThread(task);
  StringStream ss;
  ss << "fragment shader has created. id: " << id;
  Logger::trace(kOpenGLDeviceTag, ss.str());

  struct Creator : OpenGLPixelShader {
    Creator(GLuint id, const ShaderCode& code,
            std::function<void(GLuint)> on_destroy)
        : OpenGLPixelShader(id, code, on_destroy) {}
  };

  return std::make_shared<Creator>(id, code, [this](GLuint id) {
    auto task = [id]() { glCallWithErrorCheck(glDeleteShader, id); };
    execInLoadThread(task);
    StringStream ss;
    ss << "fragment shader has deleted. id: " << id;
    Logger::trace(kOpenGLDeviceTag, ss.str());
  });
}

VertexShaderSPtr OpenGLDevice::createVertexShader(const ShaderCode& code) {
  using temp::core::Logger;

  auto task = [this, code]() {
    GLuint id = glCallWithErrorCheck(glCreateShader, GL_VERTEX_SHADER);
    if (!code.is_binary_) {
      const GLchar* p_code = code.code_.c_str();
      GLint length = static_cast<GLint>(code.code_.size());
      glCallWithErrorCheck(glShaderSource, id, 1, &p_code, &length);
      glCallWithErrorCheck(glCompileShader, id);
      printShaderCompileInfoLog(id);
    } else {
    }

    return id;
  };

  GLuint id = execInLoadThread(task);
  StringStream ss;
  ss << "vertex shader has created. id: " << id;
  Logger::trace(kOpenGLDeviceTag, ss.str());

  struct Creator : OpenGLVertexShader {
    Creator(GLuint id, const ShaderCode& code,
            std::function<void(GLuint)> on_destroy)
        : OpenGLVertexShader(id, code, on_destroy) {}
  };

  return std::make_shared<Creator>(id, code, [this](GLuint id) {
    auto task = [id]() { glCallWithErrorCheck(glDeleteShader, id); };
    execInLoadThread(task);
    StringStream ss;
    ss << "vertex shader has deleted. id: " << id;
    Logger::trace(kOpenGLDeviceTag, ss.str());
  });
}

template <typename TaskType>
auto OpenGLDevice::execInLoadThread(TaskType task) -> decltype(task()) {
  bool is_res_creation_thread = false;
  auto&& this_thread_id = std::this_thread::get_id();
  auto&& load_thread_id = load_thread_->threadId(0);
  if (this_thread_id == load_thread_id) {
    is_res_creation_thread = true;
  }

  if (is_res_creation_thread) {
    return task();
  } else {
    auto&& future = load_thread_->pushTask(0, task);
    return future.get();
  }
}

OpenGLIndexBuffer::OpenGLIndexBuffer(GLuint id, const IndexBufferDesc& desc,
                                     std::function<void(GLuint)> on_destroy)
    : id_(id), on_destroy_(on_destroy) {
  desc_ = desc;
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() { on_destroy_(id_); }

const ByteData OpenGLIndexBuffer::data() {
  glCallWithErrorCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, id());
  GLint size;
  glCallWithErrorCheck(glGetBufferParameteriv, GL_ELEMENT_ARRAY_BUFFER,
                       GL_BUFFER_SIZE, &size);
  ByteData byte_data(size);
  auto mapped =
      glCallWithErrorCheck(glMapBuffer, GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
  memcpy(&byte_data[0], mapped, size);
  glCallWithErrorCheck(glUnmapBuffer, GL_ELEMENT_ARRAY_BUFFER);
  glCallWithErrorCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);

  return byte_data;
}

OpenGLPixelShader::OpenGLPixelShader(GLuint id, const ShaderCode& code,
                                     std::function<void(GLuint)> on_destroy)
    : id_(id), on_destroy_(on_destroy) {
  code_ = code;
}

OpenGLPixelShader::~OpenGLPixelShader() { on_destroy_(id_); }

OpenGLRenderTarget::OpenGLRenderTarget(GLuint id, const RenderTargetDesc& desc,
                                       std::function<void(GLuint)> on_destroy)
    : id_(id), on_destroy_(on_destroy) {
  desc_ = desc;
}

OpenGLRenderTarget::~OpenGLRenderTarget() { on_destroy_(id_); }

OpenGLTexture::OpenGLTexture(GLuint id, const TextureDesc& desc,
                             std::function<void(GLuint)> on_destroy)
    : id_(id), on_destroy_(on_destroy) {
  desc_ = desc;
}

OpenGLTexture::~OpenGLTexture() { on_destroy_(id_); }

OpenGLVertexBuffer::OpenGLVertexBuffer(GLuint id, const VertexBufferDesc& desc,
                                       std::function<void(GLuint)> on_destroy)
    : id_(id), on_destroy_(on_destroy) {
  desc_ = desc;
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() { on_destroy_(id_); }

const ByteData OpenGLVertexBuffer::data() {
  glCallWithErrorCheck(glBindBuffer, GL_ARRAY_BUFFER, id());
  GLint size;
  glCallWithErrorCheck(glGetBufferParameteriv, GL_ARRAY_BUFFER, GL_BUFFER_SIZE,
                       &size);
  ByteData byte_data(size);
  auto mapped =
      glCallWithErrorCheck(glMapBuffer, GL_ARRAY_BUFFER, GL_READ_ONLY);
  memcpy(&byte_data[0], mapped, size);
  glCallWithErrorCheck(glUnmapBuffer, GL_ARRAY_BUFFER);
  glCallWithErrorCheck(glBindBuffer, GL_ARRAY_BUFFER, 0);

  return byte_data;
}

OpenGLVertexShader::OpenGLVertexShader(GLuint id, const ShaderCode& code,
                                       std::function<void(GLuint)> on_destroy)
    : id_(id), on_destroy_(on_destroy) {
  code_ = code;
}

OpenGLVertexShader::~OpenGLVertexShader() { on_destroy_(id_); }
}  // namespace opengl
}  // namespace graphics
}  // namespace temp