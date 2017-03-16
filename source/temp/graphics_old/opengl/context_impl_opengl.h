/**
 * @file context_impl_opengl.h
 * @brief OpenGL graphics context
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-31
 */
#pragma once
#ifndef GUARD_365ecf9c64a84d8bad2321703f7c855d
#define GUARD_365ecf9c64a84d8bad2321703f7c855d

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/context.h"
#include "temp/type.h"

#include "temp/graphics_old/opengl/opengl_common.h"

namespace temp {
namespace graphics_old {

class Context::Impl {
    friend class Context;

private:
    Impl(NativeHandle& device, Context& context);
    ~Impl();
    Impl& operator=(const Impl&) = delete;

    void setBlendState(const BlendStateSPtr& blend_state);
    void setDepthStencileState(
        const DepthStencileStateSPtr& depth_stencile_state);
    void setRasterizerState(const RasterizerStateSPtr& rasterizer_state);
    void setInputLayout(const InputLayoutSPtr& input_layout);
    void setVertexBuffer(UInt32 slotNum, const VertexBufferSPtr& vertex_buffer);
    void setIndexBuffer(const IndexBufferSPtr& index_buffer);
    void setVertexShader(const VertexShaderSPtr& vertex_shader);
    void setPixelShader(const PixelShaderSPtr& pixel_shader);
    void setConstantBuffer(const String&             name,
                           const ConstantBufferSPtr& constant_buffer);
    void setTexture(const String& name, const TextureSPtr& texture);

    void draw(UInt32 vertex_count, UInt32 start_vertex_location);
    void drawIndexed(UInt32 index_count, UInt32 start_index_location,
                     Int32 base_vertex_location);

    Context& context_;

    std::unique_ptr<opengl::Command> command_;
};

}  // namespace graphics
}  // namespace temp

#endif  // TEMP_GRAPHICS_OPENGL
#endif  // GUARD_365ecf9c64a84d8bad2321703f7c855d
