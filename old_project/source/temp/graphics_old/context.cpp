/**
 * @file context.cpp
 * @brief graphics context
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-30
 */
#include "temp/graphics_old/context.h"
#if defined TEMP_GRAPHICS_D3D11
#include "temp/graphics_old/d3d11/context_impl_d3d11.h"
#elif defined TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/opengl/context_impl_opengl.h"
#endif

namespace temp {
namespace graphics_old {

Context::SPtr Context::create(NativeHandle& device) {
    struct Creator : public Context {
        Creator(NativeHandle device) : Context(device) {}
    };

    auto p = std::make_shared<Creator>(device);

    return std::move(p);
}

Context::Context(NativeHandle& device) {
    static_assert(sizeof(Impl) <= sizeof(impl_buffer_),
                  "size of impl_buffer_ is small.");
    impl_ = new (impl_buffer_) Impl(device, *this);
}

Context::~Context() {}

void Context::setBlendState(const BlendStateSPtr& blend_state) {
    impl_->setBlendState(blend_state);
}

void Context::setDepthStencileState(
    const DepthStencileStateSPtr& depth_stencile_state) {
    impl_->setDepthStencileState(depth_stencile_state);
}

void Context::setRasterizerState(const RasterizerStateSPtr& rasterizer_state) {
    impl_->setRasterizerState(rasterizer_state);
}

void Context::setInputLayout(const InputLayoutSPtr& input_layout) {
    impl_->setInputLayout(input_layout);
}

void Context::setVertexBuffer(UInt32                  slotNum,
                              const VertexBufferSPtr& vertex_buffer) {
    impl_->setVertexBuffer(slotNum, vertex_buffer);
}

void Context::setIndexBuffer(const IndexBufferSPtr& index_buffer) {
    impl_->setIndexBuffer(index_buffer);
}

void Context::setVertexShader(const VertexShaderSPtr& vertex_shader) {
    impl_->setVertexShader(vertex_shader);
}

void Context::setPixelShader(const PixelShaderSPtr& pixel_shader) {
    impl_->setPixelShader(pixel_shader);
}

void Context::setConstantBuffer(const String&             name,
                                const ConstantBufferSPtr& constant_buffer) {}

void Context::setTexture(const String& name, const TextureSPtr& texture) {}

void Context::draw(UInt32 vertex_count, UInt32 start_vertex_location) {
    impl_->draw(vertex_count, start_vertex_location);
}

void Context::drawIndexed(UInt32 index_count, UInt32 start_index_location,
                          Int32 base_vertex_location) {
    impl_->drawIndexed(index_count, start_index_location, base_vertex_location);
}

}  // namespace graphics
}  // namespace temp
