/**
 * @file opengl_vertex_shader.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-05-13
 */
#pragma once
#ifndef GUARD_dd9a884ce7fd4effb3e5faded21826de
#define GUARD_dd9a884ce7fd4effb3e5faded21826de

#include "temp/graphics_/graphics_common.h"
#include "temp/graphics_/vertex_shader.h"

#ifdef TEMP_GRAPHICS_OPENGL
namespace temp {
namespace graphics_ {
namespace opengl {

class OpenGLVertexShader : public VertexShaderBase<OpenGLVertexShader, GLuint> {
    friend class SmartPointerObject<OpenGLVertexShader>;
    friend Device;

private:
    OpenGLVertexShader(GLuint native_handle, const ShaderCode& code,
                       const std::function<void(GLuint)> on_destroy)
        : VertexShaderBase(native_handle, code, on_destroy) {}
};
}
}
}
#endif

#endif  // GUARD_dd9a884ce7fd4effb3e5faded21826de
