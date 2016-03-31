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
#include "temp/type.h"
#include "temp/graphics/context.h"

#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics {

class Context::Impl {
    friend  class Context;
private:
    Impl(Context &context);
    ~Impl();
    Impl &operator= (const Impl&) = delete;

    void setVertexBuffer(UInt32 slotNum, const VertexBufferSPtr &vertex_buffer);
    void setIndexBuffer(const IndexBufferSPtr &index_buffer);
    void setVertexShader(const VertexShaderSPtr &vertex_shader);
    void setPixelShader(const PixelShaderSPtr &pixel_shader);
    void setConstantBuffer(const String &name, const ConstantBufferSPtr &constant_buffer);
    void setTexture(const String &name, const TextureSPtr &texture);

    Context &context_;
};

} // namespace graphics
} // namespace temp

#endif // TEMP_GRAPHICS_OPENGL
#endif // GUARD_365ecf9c64a84d8bad2321703f7c855d
