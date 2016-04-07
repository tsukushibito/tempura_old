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

struct Command {
    static const Size kConstantBufferSlotCount = 128;
    static const Size kTextureSlotCount = 128;

    Bool is_valid;
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

using CommandUPtr = std::unique_ptr<Command>;

class CommandBuffer {
public:
    CommandBuffer() {
        commands_.reserve(kReservedCommandCount);
    }

    inline void pushCommand(CommandUPtr &&command) {
        commands_.push_back(std::move(command));
    }

    inline Vector<CommandUPtr> &getCommandsRef() {
        return commands_;
    }
private:
    static const Size kReservedCommandCount = 32;
    Vector<CommandUPtr> commands_;
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
