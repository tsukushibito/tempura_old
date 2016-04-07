/**
 * @file command_list_impl_opengl.h
 * @brief OpenGL command list
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-06
 */
#pragma once
#ifndef GUARD_f4973063f6ed491f9b29014643b9b2ef
#define GUARD_f4973063f6ed491f9b29014643b9b2ef

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics/command_list.h"
#include "temp/type.h"

#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics {

class BlendState;
class DepthState;
class RasterizeState;
class SamplerState;
class VertexShader;
class PixelShader;
class ConstantBuffer;
class Texture;
class VertexBuffer;
class IndexBuffer;

const Size kConstantBufferSlotCount = 128;
const Size kTextureSlotCount = 128;

struct Command {
    BlendState *blend_state;
    DepthState *depth_state;
    RasterizeState *rasterize_state;
    SamplerState *sampler_state;
    VertexShader *vertex_shader;
    PixelShader *pixel_shader;
    ConstantBuffer *constant_buffers_[kConstantBufferSlotCount];
    Texture *textures_[kTextureSlotCount];
    VertexBuffer *vertex_buffer_;
    IndexBuffer *index_buffer_;
};

class CommandList::Impl {
    friend class CommandList;

private:
    Impl(CommandList &command_list);
    ~Impl();
    Impl &operator=(const Impl &) = delete;

    CommandList &command_list_;
};
}
}

#endif // TEMP_GRAPHICS_OPENGL
#endif // GUARD_f4973063f6ed491f9b29014643b9b2ef
