/**
 * @file index_buffer.cpp
 * @brief Index Buffer
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-30
 */

#include <new>

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics_old/vertex_buffer.h"
#if defined TEMP_GRAPHICS_D3D11
#include "temp/graphics_old/d3d11/vertex_buffer_impl_d3d11.h"
#elif defined TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/opengl/index_buffer_impl_opengl.h"
#endif

namespace temp {
namespace graphics_old {

IndexBuffer::SPtr IndexBuffer::create(NativeHandle device, Size size,
                                      const void* data) {
    struct Creator : public IndexBuffer {
        Creator(NativeHandle device, Size size, const void* data)
            : IndexBuffer(device, size, data) {}
    };
    auto p = std::make_shared<Creator>(device, size, data);
    return std::move(p);
}

IndexBuffer::IndexBuffer(NativeHandle device, Size size, const void* data) {
    static_assert(sizeof(Impl) <= sizeof(impl_buffer_),
                  "size of impl_buffer_ is small.");
    impl_ = new (impl_buffer_) Impl(device, *this, size, data);
}

IndexBuffer::~IndexBuffer() { impl_->~Impl(); }

}  // namespace graphics
}  // namespace temp
