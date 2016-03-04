/**
 * @file vertex_shader_impl_opengl.cpp
 * @brief OpenGL vertex shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-04
 */
#include "temp/type.h"
#include "temp/graphics/opengl/vertex_shader_impl_opengl.h"

namespace temp {
namespace graphics {

VertexShader::Impl::Impl(const NativeHandle &native_handle) {
	id_ = native_handle.value_;
}
 
VertexShader::Impl::~Impl() {
	opengl::glCallWithErrorCheck(glDeleteShader, id_);
}
    
} // namespace graphics
} // namespace temp
