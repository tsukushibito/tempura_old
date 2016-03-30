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
	
	device.native_handle_.pointer_ = nullptr;	// OpenGL版は各スレッドでカレントに設定してあるので、OpenGLAPIで取得させることにする
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
	// auto p = std::make_shared<VertexShader>(device_.native_handle_, source, false);
    return VertexShader::create(device_.native_handle_, source, false);
}

Device::VertexShaderSPtr Device::Impl::createVertexShaderFromBinary(const String &binary) {
    return nullptr;
}

Device::PixelShaderSPtr Device::Impl::createPixelShaderFromSource(const String &source) {
    auto p = PixelShader::SPtr(new PixelShader(device_.native_handle_, source, false));
    return std::move(p);
}

Device::PixelShaderSPtr Device::Impl::createPixelShaderFromBinary(const String &binary) {
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
