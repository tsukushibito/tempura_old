/**
 * @file opengl_wrapper.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-30
 */
#pragma once
#ifndef GUARD_374a3e9b8b994b6b85cbb20ff48300f4
#define GUARD_374a3e9b8b994b6b85cbb20ff48300f4

#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/opengl_device.h"

namespace temp {
namespace render {
namespace opengl {

class VertexArrayObject {
public:
    using OpenGLVertexBufferSPtr = std::shared_ptr<graphics::opengl::OpenGLVertexBuffer>;
    using OpenGLIndexBufferSPtr  = std::shared_ptr<graphics::opengl::OpenGLIndexBuffer>;

    VertexArrayObject();
    ~VertexArrayObject();

    void setVertexBuffer(graphics::VertexAttribute     attribute,
                         const OpenGLVertexBufferSPtr& vertex_buffer);

    void setIndexBuffer(const OpenGLIndexBufferSPtr& index_buffer);

    GLuint id() const { return id_; }

    const OpenGLVertexBufferSPtr& vertexBuffer(
        graphics::VertexAttribute attribute) const {
        return vertex_buffers_[(Int32)attribute];
    }

    const OpenGLIndexBufferSPtr& indexBuffer() const { return index_buffer_; }

private:
    static const UInt32 kVertexBufferCount = (UInt32)graphics::VertexAttribute::COUNT;

    GLuint                 id_;
    OpenGLVertexBufferSPtr vertex_buffers_[kVertexBufferCount];
    OpenGLIndexBufferSPtr  index_buffer_;
};

class ProgramPiplineObject {
public:
    using OpenGLVertexShaderSPtr = std::shared_ptr<graphics::opengl::OpenGLVertexShader>;
    using OpenGLPixelShaderSPtr  = std::shared_ptr<graphics::opengl::OpenGLPixelShader>;

    ProgramPiplineObject();
    ~ProgramPiplineObject();

    GLuint id() const { return id_; }

    void setVertexShader(const OpenGLVertexShaderSPtr& vertex_shader);
    void setPixelShader(const OpenGLPixelShaderSPtr& pixel_shader);

    GLuint vertexProgram() const { return vs_program_; }
    GLuint pixelProgram() const { return ps_program_; }

    GLuint textureLocation(graphics::TextureAttribute attribute) const {
        return textureLocations_[(Int32)attribute];
    };

private:
    GLuint id_ = 0;

    OpenGLVertexShaderSPtr vertex_shader_;
    GLuint                 vs_program_ = 0;

    OpenGLPixelShaderSPtr pixel_shader_;
    GLuint                ps_program_ = 0;
    GLuint                textureLocations_[(Int32)graphics::TextureAttribute::COUNT];
};
}
}
}
#endif  // GUARD_374a3e9b8b994b6b85cbb20ff48300f4
