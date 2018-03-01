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

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/vertex_shader.h"
#include "temp/type.h"

#include "temp/graphics_old/opengl/opengl_common.h"

namespace temp {
namespace graphics_old {

class VertexShader::Impl {
    friend class VertexShader;

public:
    Impl(NativeHandle device, VertexShader& vertex_shader, const String& source,
         bool is_binary);
    ~Impl();

    Impl& operator=(const Impl&) = delete;

private:
    VertexShader& vertex_shader_;
};

}  // namespace graphics
}  // namespace temp

#endif
#endif  // GUARD_e110a8cc9a5d4543a43d5cb4644e0bb3
