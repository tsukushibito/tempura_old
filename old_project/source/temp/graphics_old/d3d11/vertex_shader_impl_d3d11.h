#pragma once
/**
 * @file vertex_shader_impl_d3d11.h
 * @brief d3d11 vertex shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-24
 */
#ifndef GUARD_7aa37733786d4a88a6e06fc8b7557758
#define GUARD_7aa37733786d4a88a6e06fc8b7557758
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_D3D11
#include "temp/type.h"
#include "temp/graphics/vertex_shader.h"

namespace temp {
namespace graphics {

class VertexShader::Impl {
    friend class VertexShader;
public:
    Impl(VertexShader &vertex_shader, const String &source, Bool is_binary);
    ~Impl();

    Impl &operator=(const Impl&) = delete;
private:
    VertexShader &vertex_shader_;
};
    
} // namespace graphics
} // namespace temp

#endif TEMP_PLATFORM_WINDOWS
#endif // GUARD_7aa37733786d4a88a6e06fc8b7557758
