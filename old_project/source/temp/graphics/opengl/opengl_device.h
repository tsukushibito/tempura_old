/**
 * @file opengl_device.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-21
 */
#pragma once
#ifndef GUARD_8709bf1374084e08b7ff2ce4964967e9
#define GUARD_8709bf1374084e08b7ff2ce4964967e9

#include "temp/system/thread_pool.h"

#include "temp/graphics/device.h"
#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics {
namespace opengl {

/**
 * @brief 
 */
class OpenGLDevice : public Device {
public:
    static Device::SPtr create(WindowHandle                    window_handle,
                               const system::ThreadPool::SPtr& render_thread,
                               const system::ThreadPool::SPtr& load_thread);

    OpenGLDevice(WindowHandle                    window_handle,
                 const system::ThreadPool::SPtr& render_thread,
                 const system::ThreadPool::SPtr& load_thread);

    ~OpenGLDevice();

    RenderTargetSPtr createRenderTarget(const RenderTargetDesc& desc);

    TextureSPtr createTexture(const TextureDesc& desc, const void* data);

    VertexBufferSPtr createVertexBuffer(const VertexBufferDesc& desc,
                                        const void*             data);

    IndexBufferSPtr createIndexBuffer(const IndexBufferDesc& desc,
                                      const void*            data);

    PixelShaderSPtr createPixelShader(const ShaderCode& code);

    VertexShaderSPtr createVertexShader(const ShaderCode& code);

    GraphicsAPI api() const { return GraphicsAPI::kOpenGL; }

    WindowHandle windowHandle() const { return window_handle_; }

    OpenGLContextHandle renderContext() const { return render_context_; }

    OpenGLContextHandle loadContext() const { return load_context_; }

    template <typename TaskType>
    auto execInLoadThread(TaskType task) -> decltype(task());

private:
    WindowHandle window_handle_;

    OpenGLContextHandle      render_context_;
    system::ThreadPool::SPtr render_thread_;

    OpenGLContextHandle      load_context_;
    system::ThreadPool::SPtr load_thread_;
};

/**
 * @brief 
 */
class OpenGLIndexBuffer : public IndexBuffer {
protected:
    OpenGLIndexBuffer(GLuint id, const IndexBufferDesc& desc,
                      std::function<void(GLuint)> on_destroy);

public:
    ~OpenGLIndexBuffer();

    const ByteData data();

    GLuint id() { return id_; }

private:
    GLuint                      id_;
    std::function<void(GLuint)> on_destroy_;
};

/**
 * @brief 
 */
class OpenGLPixelShader : public PixelShader {
protected:
    OpenGLPixelShader(GLuint id, const ShaderCode& code,
                      std::function<void(GLuint)> on_destroy);

public:
    ~OpenGLPixelShader();

    GLuint id() { return id_; }

private:
    GLuint                      id_;
    std::function<void(GLuint)> on_destroy_;
};

/**
 * @brief 
 */
class OpenGLRenderTarget : public RenderTarget {
protected:
    OpenGLRenderTarget(GLuint id, const RenderTargetDesc& desc,
                       std::function<void(GLuint)> on_destroy);

public:
    ~OpenGLRenderTarget();

    GLuint id() { return id_; }

private:
    GLuint                      id_;
    std::function<void(GLuint)> on_destroy_;
};

/**
 * @brief 
 */
class OpenGLTexture : public Texture {
protected:
    OpenGLTexture(GLuint id, const TextureDesc& desc,
                  std::function<void(GLuint)> on_destroy);

public:
    ~OpenGLTexture();

    GLuint id() { return id_; }

private:
    GLuint                      id_;
    std::function<void(GLuint)> on_destroy_;
};

/**
 * @brief 
 */
class OpenGLVertexBuffer : public VertexBuffer {
protected:
    OpenGLVertexBuffer(GLuint id, const VertexBufferDesc& desc,
                       std::function<void(GLuint)> on_destroy);

public:
    ~OpenGLVertexBuffer();

    const ByteData data();

    GLuint id() { return id_; }

private:
    GLuint                      id_;
    std::function<void(GLuint)> on_destroy_;
};

/**
 * @brief 
 */
class OpenGLVertexShader : public VertexShader {
protected:
    OpenGLVertexShader(GLuint id, const ShaderCode& code,
                       std::function<void(GLuint)> on_destroy);

public:
    ~OpenGLVertexShader();

    GLuint id() { return id_; }

private:
    GLuint                      id_;
    std::function<void(GLuint)> on_destroy_;
};
}
}
}

#endif  // GUARD_8709bf1374084e08b7ff2ce4964967e9
