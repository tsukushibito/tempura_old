/**
 * @file context_impl_opengl.cpp
 * @brief OpenGL graphics context
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-31
 */

#include "temp/define.h"
#include "temp/temp_assert.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics/opengl/context_impl_opengl.h"

#include "temp/graphics/opengl/input_layout_impl_opengl.h"

namespace temp {
namespace graphics {

Context::Impl::Impl(NativeHandle &device, Context &context)
    : context_(context)
    , command_(new opengl::Command) {
    (void)device;
}

Context::Impl::~Impl() {}

void Context::Impl::setBlendState(const BlendStateSPtr &blend_state) {
    command_->blend_state = blend_state.get();
}

void Context::Impl::setDepthStencileState(const DepthStencileStateSPtr &depth_stencile_state) {
    command_->depth_stencile_state = depth_stencile_state.get();
}

void Context::Impl::setRasterizerState(const RasterizerStateSPtr &rasterizer_state) {
    command_->rasterizer_state = rasterizer_state.get();
}

void Context::Impl::setInputLayout(const InputLayoutSPtr &input_layout) {
    command_->input_layout = input_layout.get();
}

void Context::Impl::setVertexBuffer(UInt32 slotNum, const VertexBufferSPtr &vertex_buffer) {
    TEMP_ASSERT(slotNum < opengl::Command::kVertexBufferSlotCount, "");
    command_->vertex_buffers[slotNum] = vertex_buffer.get();
}

void Context::Impl::setIndexBuffer(const IndexBufferSPtr &index_buffer) {
    command_->index_buffer = index_buffer.get();
}

void Context::Impl::setVertexShader(const VertexShaderSPtr &vertex_shader) {
    command_->vertex_shader = vertex_shader.get();
}

void Context::Impl::setPixelShader(const PixelShaderSPtr &pixel_shader) {
    command_->pixel_shader = pixel_shader.get();
}

void Context::Impl::setConstantBuffer(const String &name, const ConstantBufferSPtr &constant_buffer) {
}

void Context::Impl::setTexture(const String &name, const TextureSPtr &texture) {}

void Context::Impl::draw(UInt32 vertex_count, UInt32 start_vertex_location) {

}

void Context::Impl::drawIndexed(UInt32 index_count, UInt32 start_index_location, Int32 base_vertex_location) {

}

} // namespace graphics
} // namespace temp
#endif // TEMP_GRAPHICS_OPENGL
