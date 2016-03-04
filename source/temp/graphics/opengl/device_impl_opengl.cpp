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

#include "temp/graphics/opengl/vertex_shader_impl_opengl.h"

namespace temp {
namespace graphics {

Device::Impl::Impl(Device *device) : device_(device) {
	auto &&param = device->parameter_;
	auto &&window = param.window_;

	opengl::createContext(window->getWindowHandle().pointer_, param.worker_thread->getThreadCount());
}

Device::Impl::~Impl() {
}

Device::VertexShaderSPtr Device::Impl::createVertexShaderFromSource(const String &source) {
    return nullptr;
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
