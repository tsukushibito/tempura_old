/**
 * @file vertex_shader_impl_opengl.h
 * @brief OpenGL vertex shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-04
 */
#pragma once
#ifndef GUARD_fe1027b627864a86877d9b1c1025b0d4
#define GUARD_fe1027b627864a86877d9b1c1025b0d4

#include "temp/type.h"
#include "temp/graphics/vertex_shader.h"
#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics {

class VertexShader::Impl {
    friend class VertexShader;
private:
    Impl(const NativeHandle &native_handle);
 
    ~Impl();

private:
	GLuint id_;
};
    
} // namespace graphics
} // namespace temp
#endif // GUARD_fe1027b627864a86877d9b1c1025b0d4
