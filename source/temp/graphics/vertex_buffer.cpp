/**
 * @file vertex_buffer.cpp
 * @brief Vertex Buffer
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-29
 */

#include <new>

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics/vertex_buffer.h"
#if defined TEMP_GRAPHICS_D3D11
#include "temp/graphics/d3d11/vertex_buffer_impl_d3d11.h"
#elif defined TEMP_GRAPHICS_OPENGL
#include "temp/graphics/opengl/vertex_buffer_impl_opengl.h"
#endif

namespace temp {
namespace graphics {

VertexBuffer::SPtr VertexBuffer::create(NativeHandle device, Size size, const void *data) {
    struct Creator : public VertexBuffer {
        Creator(NativeHandle device, Size size, const void *data) : VertexBuffer(device, size, data) {}
    };
    auto p = std::make_shared< Creator >(device, size, data);
    return std::move(p);
}

VertexBuffer::VertexBuffer(NativeHandle device, Size size, const void *data) {
    static_assert(sizeof(Impl) <= sizeof(impl_buffer_), "size of impl_buffer_ is small.");
    impl_ = new (impl_buffer_) Impl(device, *this, size, data);
}

VertexBuffer::~VertexBuffer() { impl_->~Impl(); }
    
} // namespace graphics
} // namespace temp
