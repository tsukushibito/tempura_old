/**
 * @file pixel_shader_impl_opengl.cpp
 * @brief OpenGL pixel shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-29
 */
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/pixel_shader.h"

#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/pixel_shader_impl_opengl.h"

namespace temp {
namespace graphics {

PixelShader::Impl::Impl(PixelShader &pixel_shader)
    : pixel_shader_(pixel_shader) {
    temp::system::ConsoleLogger::trace("OpenGL Fragment Shader has created! id = {0}", pixel_shader_.getNativeHandle().value_);
}

PixelShader::Impl::~Impl() {
    using namespace opengl;
    GLuint pixel_shader = pixel_shader_.getNativeHandle().value_;
    glCallWithErrorCheck(glDeleteShader, pixel_shader);
    temp::system::ConsoleLogger::trace("OpenGL Fragmentx Shader has deleted! id = {0}", pixel_shader);
}

    
} // namespace graphics
} // namespace temp
#endif
