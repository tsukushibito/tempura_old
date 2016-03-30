/**
 * @file context.cpp
 * @brief graphics context
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-30
 */
#include "temp/graphics/context.h"

namespace temp {
namespace graphics {

Context::Context(const DeviceSPtr &device) {
}

Context::~Context() {
}

void Context::setVertexBuffer(UInt32 slotNum, const VertexBufferSPtr &vertex_buffer) {
}

void Context::setIndexBuffer(const IndexBufferSPtr &index_buffer) {
}

void Context::setVertexShader(const VertexShaderSPtr &vertex_shader) {
}

void Context::setPixelShader(const PixelShaderSPtr &pixel_shader) {
}

void Context::setConstantBuffer(const String &name, const ConstantBufferSPtr &constant_buffer) {
}

void Context::setTexture(const String &name, const TextureSPtr &texture) {
}

} // namespace graphics
} // namespace temp
