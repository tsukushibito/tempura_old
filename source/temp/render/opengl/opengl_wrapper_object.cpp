#include "temp/graphics/opengl/opengl_common.h"

#include "temp/render/opengl/opengl_wrapper_object.h"

namespace temp {
namespace render {
namespace opengl {

VertexArrayObject::VertexArrayObject() {
    using namespace temp::graphics::opengl;
    glCallWithErrorCheck(glGenVertexArrays, 1, &id_);
}
VertexArrayObject::~VertexArrayObject() {
    using namespace temp::graphics::opengl;
    glCallWithErrorCheck(glDeleteVertexArrays, 1, &id_);
}

void VertexArrayObject::setVertexBuffer(VertexAttribute         attribute,
                                        const VertexBufferSPtr& vertex_buffer) {
    using namespace temp::graphics::opengl;
    TEMP_ASSERT(VertexAttribute::kPosition <= attribute
                    && attribute <= VertexAttribute::COUNT,
                "");

    glCallWithErrorCheck(glBindVertexArray, id_);

    if (vertex_buffer == nullptr) {
        vertex_buffers_[(Int32)attribute] = nullptr;

        glCallWithErrorCheck(glDisableVertexAttribArray, (GLuint)attribute);

    } else {
        auto desc = vertex_buffer->desc();
        TEMP_ASSERT(attribute == desc.attribute, "");

        vertex_buffers_[(Int32)desc.attribute] = vertex_buffer;

        glCallWithErrorCheck(glEnableVertexAttribArray, (GLuint)attribute);

        auto vbo = vertex_buffer->nativeHandle();

        glCallWithErrorCheck(glBindBuffer, GL_ARRAY_BUFFER, vbo);

        auto          index      = (GLuint)desc.attribute;
        GLint         size       = 4;
        GLenum        type       = GL_FLOAT;
        GLboolean     normalized = GL_FALSE;
        GLsizei       stride     = 0;
        const GLvoid* pointer    = 0;

        switch (desc.format) {
        case temp::graphics::VertexBufferFormat::kUInt8x4:
            size = 4;
            type = GL_UNSIGNED_BYTE;
            break;
        case temp::graphics::VertexBufferFormat::kFloat16x2:
            size = 2;
            type = GL_HALF_FLOAT;
            break;
        case temp::graphics::VertexBufferFormat::kFloat16x4:
            size = 4;
            type = GL_HALF_FLOAT;
            break;
        case temp::graphics::VertexBufferFormat::kFloat32x2:
            size = 2;
            type = GL_FLOAT;
            break;
        case temp::graphics::VertexBufferFormat::kFloat32x4:
            size = 4;
            type = GL_FLOAT;
            break;
        default:
            break;
        }

        glCallWithErrorCheck(glVertexAttribPointer, index, size, type,
                             normalized, stride, pointer);
    }

    glCallWithErrorCheck(glBindVertexArray, 0);
}

void VertexArrayObject::setIndexBuffer(const IndexBufferSPtr& index_buffer) {
    using namespace temp::graphics::opengl;
    index_buffer_ = index_buffer;

    glCallWithErrorCheck(glBindVertexArray, id_);

    if (index_buffer_ == nullptr) {
        glCallWithErrorCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);

    } else {
        auto ibo = index_buffer_->nativeHandle();

        glCallWithErrorCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, ibo);
    }

    glCallWithErrorCheck(glBindVertexArray, 0);
}


ProgramPiplineObject::ProgramPiplineObject() {
    using namespace temp::graphics::opengl;
    glCallWithErrorCheck(glGenProgramPipelines, 1, &id_);
}

ProgramPiplineObject::~ProgramPiplineObject() {
    using namespace temp::graphics::opengl;
    glCallWithErrorCheck(glUseProgramStages, id_, GL_VERTEX_SHADER_BIT, 0);
    glCallWithErrorCheck(glDeleteProgram, vs_program_);
    glCallWithErrorCheck(glUseProgramStages, id_, GL_FRAGMENT_SHADER_BIT, 0);
    glCallWithErrorCheck(glDeleteProgram, ps_program_);
    glCallWithErrorCheck(glDeleteProgramPipelines, 1, &id_);
}

void ProgramPiplineObject::setVertexShader(
    const VertexShaderSPtr& vertex_shader) {
    using namespace temp::graphics::opengl;
    using namespace temp::graphics;
    vertex_shader_ = vertex_shader;

    if (vertex_shader_ == nullptr) {
        glCallWithErrorCheck(glUseProgramStages, id_, GL_VERTEX_SHADER_BIT, 0);
        glCallWithErrorCheck(glDeleteProgram, vs_program_);
    }

    auto vs = vertex_shader_->vertexShader();

    TEMP_ASSERT(vs, "");
    auto vso    = vs->nativeHandle();
    vs_program_ = glCallWithErrorCheck(glCreateProgram);
    glCallWithErrorCheck(glProgramParameteri, vs_program_, GL_PROGRAM_SEPARABLE,
                         GL_TRUE);
    glCallWithErrorCheck(glAttachShader, vs_program_, vso);
    for (GLuint i = 0; i < (GLuint)VertexAttribute::COUNT; ++i) {
        glCallWithErrorCheck(glBindAttribLocation, vs_program_, (GLuint)i,
                             vertexAttributeString((VertexAttribute)i).c_str());
    }
    glCallWithErrorCheck(glLinkProgram, vs_program_);

    GLint param;
    glCallWithErrorCheck(glGetShaderiv, vso, GL_COMPILE_STATUS, &param);
    if (param != GL_TRUE) {
        TEMP_ASSERT(false, "");
    }
    glCallWithErrorCheck(glGetProgramiv, vs_program_, GL_LINK_STATUS, &param);
    if (param != GL_TRUE) {
        TEMP_ASSERT(false, "");
    }

    glCallWithErrorCheck(glUseProgramStages, id_, GL_VERTEX_SHADER_BIT,
                         vs_program_);
}

void ProgramPiplineObject::setPixelShader(const PixelShaderSPtr& pixel_shader) {
    using namespace temp::graphics::opengl;
    pixel_shader_ = pixel_shader;

    if (pixel_shader_ == nullptr) {
        glCallWithErrorCheck(glUseProgramStages, ps_program_,
                             GL_FRAGMENT_SHADER_BIT, 0);
        glCallWithErrorCheck(glDeleteProgram, ps_program_);
    }

    auto ps = pixel_shader_->pixelShader();

    TEMP_ASSERT(ps, "");
    auto pso    = ps->nativeHandle();
    ps_program_ = glCallWithErrorCheck(glCreateProgram);
    glCallWithErrorCheck(glProgramParameteri, ps_program_, GL_PROGRAM_SEPARABLE,
                         GL_TRUE);
    glCallWithErrorCheck(glAttachShader, ps_program_, pso);
    glCallWithErrorCheck(glBindFragDataLocation, ps_program_, 0, "Color0");
    glCallWithErrorCheck(glLinkProgram, ps_program_);

    for (Int32 i = 0; i < (Int32)TextureAttribute::COUNT; ++i) {
        auto location = glCallWithErrorCheck(
            glGetUniformLocation, ps_program_,
            textureAttributeString((TextureAttribute)i).c_str());
        textureLocations_[i] = location;
    }

    GLint param;
    glCallWithErrorCheck(glGetShaderiv, pso, GL_COMPILE_STATUS, &param);
    if (param != GL_TRUE) {
        TEMP_ASSERT(false, "");
    }
    glCallWithErrorCheck(glGetProgramiv, ps_program_, GL_LINK_STATUS, &param);
    if (param != GL_TRUE) {
        TEMP_ASSERT(false, "");
    }

    glCallWithErrorCheck(glUseProgramStages, id_, GL_FRAGMENT_SHADER_BIT,
                         ps_program_);
}
}
}
}
