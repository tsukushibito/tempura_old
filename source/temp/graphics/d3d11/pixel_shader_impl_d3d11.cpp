/**
 * @file vertex_shader_impl_d3d11.cpp
 * @brief d3d11 vertex shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-24
 */
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_D3D11
#include "temp/type.h"
#include "temp/graphics/vertex_shader.h"

#include "temp/graphics/d3d11/pixel_shader_impl_d3d11.h"

namespace temp {
namespace graphics {

PixelShader::Impl::Impl(PixelShader &pixel_shader, const String &source, Bool is_binary) 
    : pixel_shader_(pixel_shader) {
}

PixelShader::Impl::~Impl() {
}

    
} // namespace graphics
} // namespace temp

#endif // TEMP_PLATFORM_WINDOWS
