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
	glCompileShader(vertex_shader);

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
