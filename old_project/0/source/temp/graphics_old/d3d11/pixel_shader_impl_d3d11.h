/**
 * @file pixel_shader_impl_d3d11.h
 * @brief d3d11 pixel shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-24
 */
#pragma once
#ifndef GUARD_7f8eec37253f4fc1a70e4b6155ee98e5
#define GUARD_7f8eec37253f4fc1a70e4b6155ee98e5
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_D3D11
#include "temp/type.h"
#include "temp/container.h"
#include "temp/graphics/pixel_shader.h"

namespace temp {
namespace graphics {

class PixelShader::Impl {
    friend class PixelShader;
public:
    Impl(PixelShader &pixel_shader, const String &source, Bool is_binary);
    ~Impl();

    Impl &operator=(const Impl&) = delete;
private:
    PixelShader &pixel_shader_;
};
    
} // namespace graphics
} // namespace temp

#endif TEMP_PLATFORM_WINDOWS
#endif // GUARD_7f8eec37253f4fc1a70e4b6155ee98e5
