/**
 * @file vertex_shader_impl_opengl.cpp
 * @brief OpenGL vertex shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-08
 */
#include "temp/type.h"
#include "temp/graphics/vertex_shader.h"

#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/vertex_shader_impl_opengl.h"

namespace temp {
namespace graphics {

VertexShader::Impl::Impl(VertexShader &vertex_shader) 
	: vertex_shader_(vertex_shader) {
}

VertexShader::Impl::~Impl() {
	using namespace opengl;
	GLuint vertex_shader = vertex_shader_.getNativeHandle().value_;
	glCallWithErrorCheck(glDeleteShader, vertex_shader);
}

    
} // namespace graphics
} // namespace temp