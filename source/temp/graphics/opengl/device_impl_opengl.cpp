/**
 * @file device_impl_opengl.cpp
 * @brief opengl graphics device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-28
 */

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/system/thread_pool.h"
#include "temp/system/window.h"

#include "temp/graphics/device.h"
#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/device_impl_opengl.h"

#include "temp/graphics/vertex_shader.h"
#include "temp/graphics/pixel_shader.h"

namespace temp {
namespace graphics {

Device::Impl::Impl(Device &device) : device_(device) {
    auto &&param = device_.parameter_;
    auto &&window = param.window;
    auto &&worker = param.worker_thread;
    contexts_ = opengl::createContexts(window->getWindowHandle().pointer_, worker->getThreadCount());

    // 各スレッドでコンテキストをカレントに設定
    auto window_handle = window->getWindowHandle().pointer_;
    // app thread
    opengl::makeCurrent(window_handle, contexts_.context_for_application_thread);
    // main thread
    auto future = param.main_thread->pushJob(
        [this, &window_handle](){opengl::makeCurrent(window_handle, contexts_.context_for_main_thread); });
    future.wait();
    // render thread
    future = param.render_thread->pushJob(
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
    // opengl::deleteContexts(contexts_);   // ウィンドウ削除後に呼び出されるとエラーとなるため、一旦明示的に破棄は行わない
}

Device::ContextSPtr Device::Impl::createContext() {
    return nullptr;
}

Device::VertexBufferSPtr Device::Impl::createVertexBuffer(Size buffer_size) {
    return nullptr;
}

Device::IndexBufferSPtr Device::Impl::createIndexBuffer(Size buffer_size) {
    return nullptr;
}

Device::ConstantBufferSPtr Device::Impl::createConstantBuffer(Size buffer_size) {
    return nullptr;
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
    using namespace opengl;
    GLuint pixel_shader = glCallWithErrorCheck(glCreateShader, GL_FRAGMENT_SHADER);
    const GLchar *src_string = source.c_str();
    const GLint length = static_cast<GLint>(source.size());
    glCallWithErrorCheck(glShaderSource, pixel_shader, (GLsizei)1, &src_string, &length);
    glCallWithErrorCheck(glCompileShader, pixel_shader);

    GLsizei size, len;
    glGetShaderiv(pixel_shader, GL_INFO_LOG_LENGTH, &size);
    if (size > 1) {
        Vector<char> log(size);
        glGetShaderInfoLog(pixel_shader, size, &len, &log[0]);
        system::ConsoleLogger::trace("[OpenGL shader info log] \n{0}", &log[0]);
    }

    NativeHandle native_handle;
    native_handle.value_ = pixel_shader;
    
    auto p = PixelShader::SPtr(new PixelShader(native_handle));
    return std::move(p);
}

Device::PixelShaderSPtr Device::Impl::createPixelShaderFromBinary(const String &binary) {
    return nullptr;
}

Device::ShaderProgramSPtr Device::Impl::createShaderProgram(const VertexShaderSPtr &vertex_shader, const PixelShaderSPtr &pixel_shader) {
	using namespace opengl;
	auto program = glCallWithErrorCheck(glCreateProgram);

	GLuint vs = vertex_shader->getNativeHandle().value_;
	GLuint ps = pixel_shader->getNativeHandle().value_;

	glCallWithErrorCheck(glAttachShader, program, vs);
	glCallWithErrorCheck(glAttachShader, program, ps);

	glCallWithErrorCheck(glLinkProgram, program);
	GLint linked;
	glCallWithErrorCheck(glGetProgramiv, program, GL_LINK_STATUS, &linked);

	printProgramInfoLog(program);
	if (linked == GL_FALSE) return nullptr;

	return nullptr;
}

void Device::Impl::executeCommands(const Device::ContextSPtr &context) {
}

void Device::Impl::present() {
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    auto &&param = device_.parameter_;
    auto &&window = param.window;
    opengl::swapBuffers(window->getWindowHandle().pointer_, contexts_.context_for_render_thread);
}

} // namespace graphics
} // namespace temp
#endif
