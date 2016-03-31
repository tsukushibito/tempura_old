/**
 * @file context_impl_opengl.cpp
 * @brief OpenGL graphics context
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-31
 */

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics/opengl/context_impl_opengl.h"

namespace temp {
namespace graphics {

Context::Impl::Impl(Context &context) 
    : context_(context) {
}

Context::Impl::~Impl() {
}

void Context::Impl::setVertexBuffer(UInt32 slotNum, const VertexBufferSPtr &vertex_buffer) {
}

void Context::Impl::setIndexBuffer(const IndexBufferSPtr &index_buffer) {
}

void Context::Impl::setVertexShader(const VertexShaderSPtr &vertex_shader) {
}

void Context::Impl::setPixelShader(const PixelShaderSPtr &pixel_shader) {
}

void Context::Impl::setConstantBuffer(const String &name, const ConstantBufferSPtr &constant_buffer) {
}

void Context::Impl::setTexture(const String &name, const TextureSPtr &texture) {
}

    
} // namespace graphics
} // namespace temp
#endif // TEMP_GRAPHICS_OPENGL
