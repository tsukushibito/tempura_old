/**
 * @file opengl_device.cpp
 * @brief OpenGL device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-14
 */

#include "temp/define.h"

#include "temp/system/logger.h"

#include "temp/graphics/opengl/opengl_common.h"
#if defined(TEMP_PLATFORM_MAC)
#include "temp/graphics/opengl/mac/opengl_mac.h"
#elif defined(TEMP_PLATFORM_WINDOWS)
#include "temp/graphics/opengl/windows/opengl_windows.h"
#endif
#include "temp/graphics/opengl/opengl_device.h"
#include "temp/graphics/opengl/opengl_index_buffer.h"
#include "temp/graphics/opengl/opengl_pixel_shader.h"
#include "temp/graphics/opengl/opengl_texture.h"
#include "temp/graphics/opengl/opengl_vertex_buffer.h"
#include "temp/graphics/opengl/opengl_vertex_shader.h"

#include "temp/system/window.h"

namespace temp {
namespace graphics {
namespace opengl {

OpenGLDevice::OpenGLDevice(NativeWindowHandle window_handle)
    : resource_creation_thread_(
          temp::system::ThreadPool::makeUnique("OpenGL resource create", 1)) {
#if defined(TEMP_PLATFORM_MAC)
    native_handle_ = mac::createContext(window_handle);
    resource_creation_thread_->pushJob(
        [this]() { mac::makeCurrent(native_handle_); });
#elif defined(TEMP_PLATFORM_WINDOWS)
    native_handle_ = windows::createContext(window_handle);
    resource_creation_thread_->pushJob(
        [this, window_handle]() { 
		auto hdc = GetDC(window_handle);
		wglMakeCurrent(hdc, native_handle_); 
	});
#endif
}

OpenGLTexture::SPtr OpenGLDevice::createTexture(const TextureDesc& desc) {
    using temp::system::Logger;

    auto task = [this, &desc]() {
        GLuint id;
        glCallWithErrorCheck(glGenTextures, 1, &id);
        return id;
    };

    GLuint id = execInResourceCreationThread(task);
	Logger::trace("[OpenGL] texture has created. id: {0}", id);

    return Texture::makeShared(id, desc, [this](GLuint id) {
        auto task = [id]() { glCallWithErrorCheck(glDeleteTextures, 1, &id); };
        execInResourceCreationThread(task);
        Logger::trace("[OpenGL] texture has deleted. id: {0}", id);
    });
}

OpenGLPixelShader::SPtr OpenGLDevice::createPixelShader(
    const ShaderCode& code) {
    using temp::system::Logger;

    auto task = [this, &code]() {
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

    auto task = [this, &code]() {
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

template <typename TaskType>
auto OpenGLDevice::execInResourceCreationThread(TaskType& task)
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
