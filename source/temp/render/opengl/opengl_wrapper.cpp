#include "temp/render/opengl/opengl_wrapper.h"

namespace temp {
namespace render {
namespace opengl {

VertexArrayObject::VertexArrayObject() {
    graphics::opengl::glCallWithErrorCheck(glGenVertexArrays, 1, &id_);
}
VertexArrayObject::~VertexArrayObject() {
    graphics::opengl::glCallWithErrorCheck(glDeleteVertexArrays, 1, &id_);
}

void VertexArrayObject::setVertexBuffer(
    graphics::VertexAttribute attribute, const OpenGLVertexBufferSPtr& vertex_buffer) {
    
    using namespace graphics;
    using namespace graphics::opengl;
    
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

        auto vbo = vertex_buffer->id();

        glCallWithErrorCheck(glBindBuffer, GL_ARRAY_BUFFER, vbo);

        auto          index      = (GLuint)desc.attribute;
        GLint         size       = 4;
        GLenum        type       = GL_FLOAT;
        GLboolean     normalized = GL_FALSE;
        GLsizei       stride     = 0;
        const GLvoid* pointer    = 0;

        switch (desc.format) {
        case VertexBufferFormat::kUInt8x4:
            size = 4;
            type = GL_UNSIGNED_BYTE;
            break;
        case VertexBufferFormat::kFloat16x2:
            size = 2;
            type = GL_HALF_FLOAT;
            break;
        case VertexBufferFormat::kFloat16x4:
            size = 4;
            type = GL_HALF_FLOAT;
            break;
        case VertexBufferFormat::kFloat32x2:
            size = 2;
            type = GL_FLOAT;
            break;
        case VertexBufferFormat::kFloat32x4:
            size = 4;
            type = GL_FLOAT;
            break;
        default:
            break;
        }

        glCallWithErrorCheck(glVertexAttribPointer, index, size, type,
                             normalized, stride, pointer);

        ByteData data(desc.size);
        glCallWithErrorCheck(glGetBufferSubData, GL_ARRAY_BUFFER, 0, desc.size,
                             &data[0]);
        glCallWithErrorCheck(glBufferData, GL_ARRAY_BUFFER, desc.size, &data[0],
                             GL_STATIC_DRAW);
        // Float32 p[256];
        // glCallWithErrorCheck(glGetBufferSubData, GL_ARRAY_BUFFER, 0,
        // desc.size, p);
        // glCallWithErrorCheck(glBufferData, GL_ARRAY_BUFFER, desc.size, p,
        // GL_STATIC_DRAW);
    }

    glCallWithErrorCheck(glBindVertexArray, 0);
}

void VertexArrayObject::setIndexBuffer(
    const OpenGLIndexBufferSPtr& index_buffer) {
    
    using namespace graphics;
    using namespace graphics::opengl;
    
    index_buffer_ = index_buffer;

    glCallWithErrorCheck(glBindVertexArray, id_);

    if (index_buffer_ == nullptr) {
        glCallWithErrorCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, 0);

    } else {
        auto ibo = index_buffer_->id();

        glCallWithErrorCheck(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, ibo);

        auto&&   desc = index_buffer_->desc();
        ByteData data(desc.size);
        glCallWithErrorCheck(glGetBufferSubData, GL_ELEMENT_ARRAY_BUFFER, 0,
                             desc.size, &data[0]);
        glCallWithErrorCheck(glBufferData, GL_ELEMENT_ARRAY_BUFFER, desc.size,
                             &data[0], GL_STATIC_DRAW);
        // Float32 p[256];
        // glCallWithErrorCheck(glGetBufferSubData, GL_ARRAY_BUFFER, 0,
        // desc.size, p);
        // glCallWithErrorCheck(glBufferData, GL_ARRAY_BUFFER, desc.size, p,
        // GL_STATIC_DRAW);
    }

    glCallWithErrorCheck(glBindVertexArray, 0);
}


ProgramPiplineObject::ProgramPiplineObject() {
    using namespace graphics;
    using namespace graphics::opengl;
    
    glCallWithErrorCheck(glGenProgramPipelines, 1, &id_);
}

ProgramPiplineObject::~ProgramPiplineObject() {
    using namespace graphics;
    using namespace graphics::opengl;
    
    glCallWithErrorCheck(glUseProgramStages, id_, GL_VERTEX_SHADER_BIT, 0);
    glCallWithErrorCheck(glDeleteProgram, vs_program_);
    glCallWithErrorCheck(glUseProgramStages, id_, GL_FRAGMENT_SHADER_BIT, 0);
    glCallWithErrorCheck(glDeleteProgram, ps_program_);
    glCallWithErrorCheck(glDeleteProgramPipelines, 1, &id_);
}

void ProgramPiplineObject::setVertexShader(
    const OpenGLVertexShaderSPtr& vertex_shader) {
    using namespace graphics;
    using namespace graphics::opengl;
    
    vertex_shader_ = vertex_shader;

    if (vertex_shader_ == nullptr) {
        glCallWithErrorCheck(glUseProgramStages, id_, GL_VERTEX_SHADER_BIT, 0);
        glCallWithErrorCheck(glDeleteProgram, vs_program_);
    }

    auto vs = vertex_shader_->id();

    GLint param;
    glCallWithErrorCheck(glGetShaderiv, vs, GL_COMPILE_STATUS, &param);
    if (param != GL_TRUE) {
        TEMP_ASSERT(false, "");
    }

    vs_program_ = glCallWithErrorCheck(glCreateProgram);
    glCallWithErrorCheck(glProgramParameteri, vs_program_, GL_PROGRAM_SEPARABLE,
                         GL_TRUE);
    glCallWithErrorCheck(glAttachShader, vs_program_, vs);
    for (GLuint i = 0; i < (GLuint)VertexAttribute::COUNT; ++i) {
        glCallWithErrorCheck(glBindAttribLocation, vs_program_, (GLuint)i,
                             vertexAttributeString((VertexAttribute)i).c_str());
    }
    glCallWithErrorCheck(glLinkProgram, vs_program_);

    glCallWithErrorCheck(glGetProgramiv, vs_program_, GL_LINK_STATUS, &param);
    if (param != GL_TRUE) {
        GLint maxLength = 0;
        glGetProgramiv(vs_program_, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        if (maxLength > 0) {
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(vs_program_, maxLength, &maxLength,
                                &infoLog[0]);
            TEMP_ASSERT(false, &infoLog[0]);
        }
    }

    glCallWithErrorCheck(glUseProgramStages, id_, GL_VERTEX_SHADER_BIT,
                         vs_program_);
}

void ProgramPiplineObject::setPixelShader(
    const OpenGLPixelShaderSPtr& pixel_shader) {
    using namespace graphics;
    using namespace graphics::opengl;
    
    pixel_shader_ = pixel_shader;

    if (pixel_shader_ == nullptr) {
        glCallWithErrorCheck(glUseProgramStages, ps_program_,
                             GL_FRAGMENT_SHADER_BIT, 0);
        glCallWithErrorCheck(glDeleteProgram, ps_program_);
    }

    auto ps    = pixel_shader_->id();
    ps_program_ = glCallWithErrorCheck(glCreateProgram);
    glCallWithErrorCheck(glProgramParameteri, ps_program_, GL_PROGRAM_SEPARABLE,
                         GL_TRUE);
    glCallWithErrorCheck(glAttachShader, ps_program_, ps);
    glCallWithErrorCheck(glBindFragDataLocation, ps_program_, 0, "Color0");
    glCallWithErrorCheck(glLinkProgram, ps_program_);

    for (Int32 i = 0; i < (Int32)TextureAttribute::COUNT; ++i) {
        auto location = glCallWithErrorCheck(
            glGetUniformLocation, ps_program_,
            textureAttributeString((TextureAttribute)i).c_str());
        textureLocations_[i] = location;
    }

    GLint param;
    glCallWithErrorCheck(glGetShaderiv, ps, GL_COMPILE_STATUS, &param);
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
