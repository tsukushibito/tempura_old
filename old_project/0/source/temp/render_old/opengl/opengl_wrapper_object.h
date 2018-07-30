/**
 * @file opengl_wrapper_object.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-14
 */
#pragma once
#ifndef GUARD_f39fc5c2b6f546a9b860e28b18661f72
#define GUARD_f39fc5c2b6f546a9b860e28b18661f72

#include "temp/define.h"
#include "temp/type.h"

#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics_/opengl/opengl_define.h"

#include "temp/graphics_/graphics.h"

#include "temp/resource_old/resource.h"

#include "temp/render_old/render_common.h"

namespace temp {
namespace render_old {
namespace opengl {

class VertexArrayObject {
public:
    using VertexBufferSPtr = temp::graphics_::VertexBufferSPtr;
    using IndexBufferSPtr  = temp::graphics_::IndexBufferSPtr;
    using VertexAttribute  = temp::graphics_::VertexAttribute;

    VertexArrayObject();
    ~VertexArrayObject();

    void setVertexBuffer(VertexAttribute         attribute,
                         const VertexBufferSPtr& vertex_buffer);

    void setIndexBuffer(const IndexBufferSPtr& index_buffer);

    GLuint id() const { return id_; }

    const VertexBufferSPtr& vertexBuffer(
        temp::graphics_::VertexAttribute attribute) const {
        return vertex_buffers_[(Int32)attribute];
    }

    const IndexBufferSPtr& indexBuffer() const { return index_buffer_; }

private:
    static const UInt32 kVertexBufferCount
        = (UInt32)temp::graphics_::VertexAttribute::COUNT;

    GLuint           id_;
    VertexBufferSPtr vertex_buffers_[kVertexBufferCount];
    IndexBufferSPtr  index_buffer_;
};

class ProgramPiplineObject {
public:
    using ThreadPoolSPtr   = temp::system::ThreadPool::SPtr;
    using VertexShaderSPtr = temp::resource_old::VertexShader::SPtr;
    using PixelShaderSPtr  = temp::resource_old::PixelShader::SPtr;

    ProgramPiplineObject();
    ~ProgramPiplineObject();

    GLuint id() const { return id_; }

    void setVertexShader(const VertexShaderSPtr& vertex_shader);
    void setPixelShader(const PixelShaderSPtr& pixel_shader);

    GLuint vertexProgram() const { return vs_program_; }
    GLuint pixelProgram() const { return ps_program_; }

    GLuint textureLocation(TextureAttribute attribute) const {
        return textureLocations_[(Int32)attribute];
    };

private:
    GLuint id_ = 0;

    VertexShaderSPtr vertex_shader_;
    GLuint           vs_program_ = 0;

    PixelShaderSPtr pixel_shader_;
    GLuint          ps_program_ = 0;
    GLuint          textureLocations_[(Int32)TextureAttribute::COUNT];
};
}
}
}
#endif

#endif  // GUARD_f39fc5c2b6f546a9b860e28b18661f72
