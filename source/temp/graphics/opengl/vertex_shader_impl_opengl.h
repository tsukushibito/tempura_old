/**
 * @file vertex_shader_impl_opengl.h
 * @brief OpenGL vertex shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-08
 */
#pragma once
#ifndef GUARD_e110a8cc9a5d4543a43d5cb4644e0bb3
#define GUARD_e110a8cc9a5d4543a43d5cb4644e0bb3

#include "temp/type.h"
#include "temp/graphics/vertex_shader.h"

#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics {

class VertexShader::Impl {
    friend class VertexShader;
public:
    Impl(VertexShader &vertex_shader);
    ~Impl();

	Impl &operator=(const Impl&) = delete;
private:
	VertexShader &vertex_shader_;
};
    
} // namespace graphics
} // namespace temp

#endif // GUARD_e110a8cc9a5d4543a43d5cb4644e0bb3
