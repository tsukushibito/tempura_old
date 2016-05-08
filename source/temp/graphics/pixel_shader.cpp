/**
 * @file pixel_shader.cpp
 * @brief pixel shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-29
 */
#include <new>

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics/pixel_shader.h"
#if defined TEMP_GRAPHICS_D3D11
#include "temp/graphics/d3d11/pixel_shader_impl_d3d11.h"
#elif defined TEMP_GRAPHICS_OPENGL
#include "temp/graphics/opengl/pixel_shader_impl_opengl.h"
#endif

namespace temp {
namespace graphics {

PixelShader::SPtr PixelShader::create(NativeHandle device, const String &source, Bool is_binary) {
    struct Creator : public PixelShader {
        Creator(NativeHandle device, const String &source, Bool is_binary) : PixelShader(device, source, is_binary) {}
    };
    auto p = std::make_shared< Creator >(device, source, is_binary);
    return std::move(p);
}

PixelShader::PixelShader(NativeHandle device, const String &source, Bool is_binary) 
{
    static_assert(sizeof(Impl) <= sizeof(impl_buffer_), "size of impl_buffer_ is small.");
    impl_ = new(impl_buffer_) Impl(device, *this, source, is_binary);
}

PixelShader::~PixelShader() {
    impl_->~Impl();
}

} // namespace graphics
} // namespace temp
