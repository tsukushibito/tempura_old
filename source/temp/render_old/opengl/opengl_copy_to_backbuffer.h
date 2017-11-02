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

#include "temp/graphics_/graphics.h"

#include "temp/resource_old/pixel_shader.h"
#include "temp/resource_old/vertex_shader.h"

#include "temp/render_old/renderer.h"

#include "temp/render_old/opengl/opengl_wrapper_object.h"

namespace temp {
namespace render_old {
namespace opengl {

class CopyToBackBuffer {
public:
    using GraphicsDeviceSPtr  = temp::graphics_::DeviceSPtr;
    using VertexBufferSPtr    = temp::graphics_::VertexBufferSPtr;
    using IndexBufferSPtr     = temp::graphics_::IndexBufferSPtr;
    using ResVertexShaderSPtr = temp::resource_old::VertexShader::SPtr;
    using ResPixelShaderSPtr  = temp::resource_old::PixelShader::SPtr;

    CopyToBackBuffer(const GraphicsDeviceSPtr& graphics_device,
                     const temp::system::Path& shader_directory);

    ~CopyToBackBuffer();

    void copy(GLuint texture, GLuint sampler);

    GLuint arrayBuffer(temp::graphics_::VertexAttribute attribute);
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
