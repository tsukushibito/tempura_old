/**
 * @file vertex_shader.cpp
 * @brief vertex shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-03
 */

#include <new>

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics/vertex_shader.h"
#if defined TEMP_GRAPHICS_D3D11
#include "temp/graphics/d3d11/vertex_shader_impl_d3d11.h"
#elif defined TEMP_GRAPHICS_OPENGL
#include "temp/graphics/opengl/vertex_shader_impl_opengl.h"
#endif

namespace temp {
namespace graphics {

VertexShader::SPtr VertexShader::create(NativeHandle device, const String &source, Bool is_binary) {
    struct Creator : public VertexShader {
        Creator(NativeHandle device, const String &source, Bool is_binary) : VertexShader(device, source, is_binary) {}
    };
    auto p = std::make_shared< Creator >(device, source, is_binary);
    return std::move(p);
}

VertexShader::VertexShader(NativeHandle device, const String &source, Bool is_binary) {
    static_assert(sizeof(Impl) <= sizeof(impl_buffer_), "size of impl_buffer_ is small.");
    impl_ = new (impl_buffer_) Impl(*this, source, is_binary);

    (void)&device; // 未使用引数
}

VertexShader::~VertexShader() { impl_->~Impl(); }

} // namespace graphics
} // namespace temp
