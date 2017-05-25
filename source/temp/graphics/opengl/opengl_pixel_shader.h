/**
 * @file opengl_pixel_shader.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-05-13
 */
#pragma once
#ifndef GUARD_4cacdf0c6c61410fb0e6c7221a48d81b
#define GUARD_4cacdf0c6c61410fb0e6c7221a48d81b

#include "temp/graphics/graphics_common.h"
#include "temp/graphics/pixel_shader.h"

#ifdef TEMP_GRAPHICS_OPENGL
namespace temp {
namespace graphics {
namespace opengl {

class OpenGLPixelShader : public PixelShaderBase<OpenGLPixelShader, GLuint> {
    friend class SmartPointerObject<OpenGLPixelShader>;
    friend Device;

private:
    OpenGLPixelShader(GLuint native_handle, const ShaderCode& code,
                      const std::function<void(GLuint)> on_destroy)
        : PixelShaderBase(native_handle, code, on_destroy) {}
};
}
}
}
#endif

#endif  // GUARD_4cacdf0c6c61410fb0e6c7221a48d81b
