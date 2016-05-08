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
    
class Context::Impl {
public:
    Impl(NativeHandle &, Context &) {}
};

Context::SPtr Context::create(NativeHandle &device) {
    struct Creator : public Context {
        Creator(NativeHandle device) : Context(device) { }
    };

    auto p = std::make_shared<Creator>(device);

    return std::move(p);
}

Context::Context(NativeHandle &device) {
    static_assert(sizeof(Impl) <= sizeof(impl_buffer_), "size of impl_buffer_ is small.");
    impl_ = new (impl_buffer_) Impl(device, *this);
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
