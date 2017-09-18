/**
 * @file opengl_copy_to_backbuffer.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-13
 */
#pragma once
#ifndef GUARD_6ed4f43b6bf442f49a99969808a44bb6
#define GUARD_6ed4f43b6bf442f49a99969808a44bb6

#include "temp/temp_math.h"

#include "temp/graphics/graphics.h"

#include "temp/resource/pixel_shader.h"
#include "temp/resource/vertex_shader.h"

#include "temp/render/renderer.h"

#include "temp/render/opengl/opengl_wrapper_object.h"

namespace temp {
namespace render {
namespace opengl {

class CopyToBackBuffer {
public:
    using GraphicsDeviceSPtr  = temp::graphics::DeviceSPtr;
    using VertexBufferSPtr    = temp::graphics::VertexBufferSPtr;
    using IndexBufferSPtr     = temp::graphics::IndexBufferSPtr;
    using ResVertexShaderSPtr = temp::resource::VertexShader::SPtr;
    using ResPixelShaderSPtr  = temp::resource::PixelShader::SPtr;

    CopyToBackBuffer(const GraphicsDeviceSPtr& graphics_device,
                     const temp::system::Path& shader_directory);

    ~CopyToBackBuffer();

    void copy(GLuint texture, GLuint sampler);

    GLuint arrayBuffer(temp::graphics::VertexAttribute attribute);
private:
    GraphicsDeviceSPtr graphics_device_;
    temp::system::Path shader_directory_;

    std::unique_ptr<opengl::VertexArrayObject>    vao_;
    std::unique_ptr<opengl::ProgramPiplineObject> ppo_;
};
}
}
}

#endif  // GUARD_6ed4f43b6bf442f49a99969808a44bb6
