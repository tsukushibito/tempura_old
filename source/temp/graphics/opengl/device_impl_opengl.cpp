/**
 * @file device_impl_opengl.cpp
 * @brief opengl graphics device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-28
 */

#include "temp/system/thread_pool.h"
#include "temp/system/window.h"

#include "temp/graphics/device.h"
#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/device_impl_opengl.h"

#include "temp/graphics/vertex_shader.h"

namespace temp {
namespace graphics {

Device::Impl::Impl(Device &device) : device_(device) {
    auto &&param = device_.parameter_;
    auto &&window = param.window;
    auto &&worker = param.worker_thread;
    contexts_ = opengl::createContexts(window->getWindowHandle().pointer_, worker->getThreadCount());

    // 各スレッドでコンテキストをカレントに設定
    auto window_handle = window->getWindowHandle().pointer_;
    // render thread
    auto future = param.render_thread->pushJob(
        [this, &window_handle](){opengl::makeCurrent(window_handle, contexts_.context_for_render_thread); });
    future.wait();
    // load thread
    future = param.load_thread->pushJob(
        [this, &window_handle](){opengl::makeCurrent(window_handle, contexts_.context_for_load_thread); });
    future.wait();
    // worker thread
    for (int i = 0; i < worker->getThreadCount(); ++i) {
        future = worker->pushJobToSpecificThreadQueue(i,
            [this, &window_handle, i](){opengl::makeCurrent(window_handle, contexts_.contexts_for_worker_thread[i]); });
        future.wait();
    }
}

Device::Impl::~Impl() {
    opengl::deleteContexts(contexts_);
}

Device::VertexShaderSPtr Device::Impl::createVertexShaderFromSource(const String &source) {
    using namespace opengl;
    GLuint vertex_shader = glCallWithErrorCheck(glCreateShader, GL_VERTEX_SHADER);
    const GLchar *src_string = source.c_str();
    const GLint length = static_cast<GLint>(source.size());
    glCallWithErrorCheck(glShaderSource, vertex_shader, (GLsizei)1, &src_string, &length);
    glCallWithErrorCheck(glCompileShader, vertex_shader);

    GLsizei size, len;
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &size);
    if (size > 1) {
        Vector<char> log(size);
        glGetShaderInfoLog(vertex_shader, size, &len, &log[0]);
        system::ConsoleLogger::trace("[OpenGL shader info log] \n{0}", &log[0]);
    }

    NativeHandle native_handle;
    native_handle.value_ = vertex_shader;
    
    auto p = VertexShader::SPtr(new VertexShader(native_handle));
    return std::move(p);
}

Device::VertexShaderSPtr Device::Impl::createVertexShaderFromBinary(const String &binary) {
    return nullptr;
}

Device::PixelShaderSPtr Device::Impl::createPixelShaderFromSource(const String &source) {
    return nullptr;
}

Device::PixelShaderSPtr Device::Impl::createPixelShaderFromBinary(const String &binary) {
    return nullptr;
}

} // namespace graphics
} // namespace temp
