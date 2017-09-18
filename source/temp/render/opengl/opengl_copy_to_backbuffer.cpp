/**
 * @file opengl_copy_to_backbuffer.cpp
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-13
 */

#include "temp/graphics/opengl/opengl_common.h"

#include "temp/render/opengl/opengl_copy_to_backbuffer.h"

namespace temp {
namespace render {
namespace opengl {

namespace {
const String kCopyVS = "/glsl/copy.vert";
const String kCopyPS = "/glsl/copy.frag";
}

CopyToBackBuffer::CopyToBackBuffer(const GraphicsDeviceSPtr& graphics_device,
                                   const temp::system::Path& shader_directory)
    : graphics_device_(graphics_device)
    , shader_directory_(shader_directory)
    , vao_(new VertexArrayObject)
    , ppo_(new ProgramPiplineObject) {
    using namespace temp::system;
    using namespace temp::graphics;
    using namespace temp::graphics::opengl;

    Path vs_path = shader_directory_ + kCopyVS;

    auto vs = resource::VertexShader::create(vs_path);
    vs->load();

    Path ps_path = shader_directory_ + kCopyPS;

    auto ps = resource::PixelShader::create(ps_path);
    ps->load();


    Float32 positions[4][2] = {
        // {1.0f, 1.0f}, {-1.0f, 1.0f}, {1.0f, -1.0f}, {-1.0f, -1.0f},
        {0.8f, 0.8f},
        {-0.8f, 0.8f},
        {0.8f, -0.8f},
        {-0.8f, -0.8f},
    };

    VertexBufferDesc vb_desc;
    vb_desc.format    = VertexBufferFormat::kFloat32x2;
    vb_desc.attribute = VertexAttribute::kPosition;
    vb_desc.size      = sizeof(positions);
    auto vb_pos = graphics_device_->createVertexBuffer(vb_desc, positions);

    auto pos_attr = vb_pos->desc().attribute;
    vao_->setVertexBuffer(pos_attr, vb_pos);

    Float32 uvs[4][2] = {
        {1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    };

    vb_desc.format    = VertexBufferFormat::kFloat32x2;
    vb_desc.attribute = VertexAttribute::kTexCoord0;
    vb_desc.size      = sizeof(uvs);
    auto vb_uv0       = graphics_device_->createVertexBuffer(vb_desc, uvs);

    auto uv0_attr = vb_uv0->desc().attribute;
    vao_->setVertexBuffer(uv0_attr, vb_uv0);

    UInt16 indices[4] = {0, 1, 2, 3};

    IndexBufferDesc ib_desc;
    ib_desc.format         = IndexBufferFormat::kUInt16;
    ib_desc.primitive_type = PrimitiveType::kTriangleStrip;
    ib_desc.size           = sizeof(indices);
    auto ib = graphics_device_->createIndexBuffer(ib_desc, indices);

    vao_->setIndexBuffer(ib);

    ppo_->setVertexShader(vs);
    ppo_->setPixelShader(ps);

}

CopyToBackBuffer::~CopyToBackBuffer() {}

void CopyToBackBuffer::copy(GLuint texture, GLuint sampler) {
    using namespace temp::graphics;
    using namespace temp::graphics::opengl;

    auto ppo = ppo_->id();
    glCallWithErrorCheck(glUseProgram, 0);
    glCallWithErrorCheck(glBindProgramPipeline, ppo);

    
    auto unit_num = (int)TextureAttribute::kAlbedoMap;
    auto ps_program = ppo_->pixelProgram();
    auto tex_loc = (GLint)ppo_->textureLocation(TextureAttribute::kAlbedoMap);
    glCallWithErrorCheck(glProgramUniform1i, ps_program, tex_loc,
                         (GLint)unit_num);

    glCallWithErrorCheck(glActiveTexture, GL_TEXTURE0 + unit_num);

    glCallWithErrorCheck(glBindTexture, GL_TEXTURE_2D, texture);
    glCallWithErrorCheck(glBindSampler, (GLuint)unit_num, sampler);

    auto vao = vao_->id();
    glCallWithErrorCheck(glBindVertexArray, vao);

    auto    ib    = vao_->indexBuffer();
    GLsizei count = (GLsizei)(ib->desc().size / indexBufferFormatSize(ib->desc().format));
    GLenum  type;
    switch (ib->desc().format) {
    case IndexBufferFormat::kUInt16:
        type = GL_UNSIGNED_SHORT;
        break;
    case IndexBufferFormat::kUInt32:
        type = GL_UNSIGNED_INT;
        break;
    default:
        type = GL_UNSIGNED_SHORT;
        break;
    }
    
    glCallWithErrorCheck(glDrawElements, GL_TRIANGLE_STRIP, count, type,
                         (const GLvoid*)0);
    
    glCallWithErrorCheck(glBindTexture, GL_TEXTURE_2D, 0);
    glCallWithErrorCheck(glBindProgramPipeline, 0);
    glCallWithErrorCheck(glBindVertexArray, 0);
}

GLuint CopyToBackBuffer::arrayBuffer(temp::graphics::VertexAttribute attribute) {
    return vao_->vertexBuffer(attribute)->nativeHandle();
}
}
}
}
