/**
 * @file opengl_device.cpp
 * @brief OpenGL device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-14
 */

#include "temp/define.h"

#include "temp/system/logger.h"

#include "temp/graphics_/opengl/opengl_common.h"
#if defined(TEMP_PLATFORM_MAC)
#include "temp/graphics_/opengl/mac/opengl_mac.h"
#elif defined(TEMP_PLATFORM_WINDOWS)
#include "temp/graphics_/opengl/windows/opengl_windows.h"
#endif
#include "temp/graphics_/opengl/opengl_device.h"
#include "temp/graphics_/opengl/opengl_index_buffer.h"
#include "temp/graphics_/opengl/opengl_pixel_shader.h"
#include "temp/graphics_/opengl/opengl_render_target.h"
#include "temp/graphics_/opengl/opengl_texture.h"
#include "temp/graphics_/opengl/opengl_vertex_buffer.h"
#include "temp/graphics_/opengl/opengl_vertex_shader.h"

#include "temp/system/window.h"

namespace temp {
namespace graphics_ {
namespace opengl {

OpenGLDevice::OpenGLDevice(NativeWindowHandle window_handle)
    : resource_creation_thread_(
          temp::system::ThreadPool::makeUnique("OpenGL resource create", 1)) {
    native_window_handle_ = window_handle;
#if defined(TEMP_PLATFORM_MAC)
    native_handle_ = mac::createContext(window_handle);
    auto job = resource_creation_thread_->pushJob(
        [this, window_handle]() { mac::makeCurrent(window_handle, native_handle_); });
    job.wait();
#elif defined(TEMP_PLATFORM_WINDOWS)
    native_handle_ = windows::createContext(window_handle);
    auto job = resource_creation_thread_->pushJob([this, window_handle]() {
        auto hdc = GetDC(window_handle);
        wglMakeCurrent(hdc, native_handle_);
    });
    job.wait();
#endif
}


OpenGLRenderTarget::SPtr OpenGLDevice::createRenderTarget(
    const RenderTargetDesc& desc) {
    using temp::system::Logger;

    auto task = [this, &desc]() {
        GLuint id;
        glCallWithErrorCheck(glGenTextures, 1, &id);
        glCallWithErrorCheck(glBindTexture, GL_TEXTURE_2D, id);

        auto   gl_format = renderTargetFormatToGlFormat(desc.format);
        GLenum gl_type   = desc.format == RenderTargetFormat::kRGBA32
                             ? GL_UNSIGNED_BYTE
                             : GL_FLOAT;
        glCallWithErrorCheck(glTexImage2D, GL_TEXTURE_2D, 0, gl_format,
                             (GLsizei)desc.width, (GLsizei)desc.height, 0, GL_RGBA, gl_type,
                             nullptr);

        glCallWithErrorCheck(glBindTexture, GL_TEXTURE_2D, 0);
        return id;
    };

    GLuint id = execInResourceCreationThread(task);
    Logger::trace("[OpenGL] render_target has created. id: {0}", id);

    return RenderTarget::makeShared(
        id, desc,
        [this](GLuint id) {
            auto task
                = [id]() { glCallWithErrorCheck(glDeleteTextures, 1, &id); };
            execInResourceCreationThread(task);
            Logger::trace("[OpenGL] render_target has deleted. id: {0}", id);
        },
        resource_creation_thread_);
}


OpenGLTexture::SPtr OpenGLDevice::createTexture(const TextureDesc& desc,
                                                const void*        data) {
    using temp::system::Logger;

    auto task = [this, &desc, data]() {
        GLuint id;
        glCallWithErrorCheck(glGenTextures, 1, &id);
        glCallWithErrorCheck(glBindTexture, GL_TEXTURE_2D, id);
		(const void*)data;
        // glCallWithErrorCheck(glTexImage2D, );
        glCallWithErrorCheck(glBindTexture, GL_TEXTURE_2D, 0);
        return id;
    };

    GLuint id = execInResourceCreationThread(task);
    Logger::trace("[OpenGL] texture has created. id: {0}", id);

    return Texture::makeShared(
        id, desc,
        [this](GLuint id) {
            auto task
                = [id]() { glCallWithErrorCheck(glDeleteTextures, 1, &id); };
            execInResourceCreationThread(task);
            Logger::trace("[OpenGL] texture has deleted. id: {0}", id);
        },
        resource_creation_thread_);
}

OpenGLVertexBuffer::SPtr OpenGLDevice::createVertexBuffer(
    const VertexBufferDesc& desc, const void* data) {
    using temp::system::Logger;

    auto task = [this, desc, data]() {
        GLuint id;
        glCallWithErrorCheck(glGenBuffers, 1, &id);
        glCallWithErrorCheck(glBindBuffer, GL_ARRAY_BUFFER, id);
        glCallWithErrorCheck(glBufferData, GL_ARRAY_BUFFER,
                             static_cast<GLsizei>(desc.size), data,
                             GL_STATIC_DRAW);
        glCallWithErrorCheck(glBindBuffer, GL_ARRAY_BUFFER, 0);
        return id;
    };

    GLuint id = execInResourceCreationThread(task);
    Logger::trace("[OpenGL] vertex buffer has created. id: {0}", id);

    return VertexBuffer::makeShared(
        id, desc,
        [this](GLuint id) {
            auto task
                = [id]() { glCallWithErrorCheck(glDeleteBuffers, 1, &id); };
            execInResourceCreationThread(task);
            Logger::trace("[OpenGL] vertex buffer has deleted. id: {0}", id);
        },
        resource_creation_thread_);
}

OpenGLIndexBuffer::SPtr OpenGLDevice::createIndexBuffer(
    const IndexBufferDesc& desc, const void* data) {
    using temp::system::Logger;

    auto task = [this, desc, data]() {
        GLuint id;
        glCallWithErrorCheck(glGenBuffers, 1, &id);
        glCallWithErrorCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, id);
        glCallWithErrorCheck(glBufferData, GL_ELEMENT_ARRAY_BUFFER,
                             static_cast<GLsizei>(desc.size), data,
                             GL_STATIC_DRAW);
        glCallWithErrorCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);
        return id;
    };

    GLuint id = execInResourceCreationThread(task);
    Logger::trace("[OpenGL] index buffer has created. id: {0}", id);

    return IndexBuffer::makeShared(
        id, desc,
        [this](GLuint id) {
            auto task
                = [id]() { glCallWithErrorCheck(glDeleteBuffers, 1, &id); };
            execInResourceCreationThread(task);
            Logger::trace("[OpenGL] index buffer has deleted. id: {0}", id);
        },
        resource_creation_thread_);
}

OpenGLPixelShader::SPtr OpenGLDevice::createPixelShader(
    const ShaderCode& code) {
    using temp::system::Logger;

    auto task = [this, code]() {
        GLuint id = glCallWithErrorCheck(glCreateShader, GL_FRAGMENT_SHADER);
        if (!code.is_binary_) {
            const GLchar* p_code = code.code_.c_str();
            GLint         length = static_cast<GLint>(code.code_.size());
            glCallWithErrorCheck(glShaderSource, id, 1, &p_code, &length);
            glCallWithErrorCheck(glCompileShader, id);
            printShaderCompileInfoLog(id);
        } else {
        }

        return id;
    };

    GLuint id = execInResourceCreationThread(task);
    Logger::trace("[OpenGL] fragment shader has created. id: {0}", id);

    return PixelShader::makeShared(id, code, [this](GLuint id) {
        auto task = [id]() { glCallWithErrorCheck(glDeleteShader, id); };
        execInResourceCreationThread(task);
        Logger::trace("[OpenGL] fragment shader has deleted. id: {0}", id);
    });
}

OpenGLVertexShader::SPtr OpenGLDevice::createVertexShader(
    const ShaderCode& code) {
    using temp::system::Logger;

    auto task = [this, code]() {
        GLuint id = glCallWithErrorCheck(glCreateShader, GL_VERTEX_SHADER);
        if (!code.is_binary_) {
            const GLchar* p_code = code.code_.c_str();
            GLint         length = static_cast<GLint>(code.code_.size());
            glCallWithErrorCheck(glShaderSource, id, 1, &p_code, &length);
            glCallWithErrorCheck(glCompileShader, id);
            printShaderCompileInfoLog(id);
        } else {
        }

        return id;
    };

    GLuint id = execInResourceCreationThread(task);
    Logger::trace("[OpenGL] vertex shader has created. id: {0}", id);

    return VertexShader::makeShared(id, code, [this](GLuint id) {
        auto task = [id]() { glCallWithErrorCheck(glDeleteShader, id); };
        execInResourceCreationThread(task);
        Logger::trace("[OpenGL] vertex shader has deleted. id: {0}", id);
    });
}

void OpenGLDevice::prepareToShare() {
#ifdef TEMP_PLATFORM_WINDOWS
    auto task = [this]() {
        auto hdc = GetDC(native_window_handle_);
        wglMakeCurrent(hdc, nullptr);
    };
    execInResourceCreationThread(task);
#endif
}

void OpenGLDevice::restoreContext() {
#ifdef TEMP_PLATFORM_WINDOWS
    auto task = [this]() {
        auto hdc = GetDC(native_window_handle_);
        wglMakeCurrent(hdc, native_handle_);
    };
    execInResourceCreationThread(task);
#endif
}

template <typename TaskType>
auto OpenGLDevice::execInResourceCreationThread(TaskType task)
    -> decltype(task()) {
    bool   is_res_creation_thread = false;
    auto&& thread_id              = std::this_thread::get_id();
    auto&& thread_id_list         = resource_creation_thread_->threadIdList();
    for (auto&& i : thread_id_list) {
        if (i == thread_id) {
            is_res_creation_thread = true;
        }
    }

    if (is_res_creation_thread) {
        return task();
    } else {
        auto&& future = resource_creation_thread_->pushJob(task);
        return future.get();
    }
}
}
}
}
