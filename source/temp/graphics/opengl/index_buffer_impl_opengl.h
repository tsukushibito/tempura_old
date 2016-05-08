/**
 * @file index_buffer_impl_opengl.h
 * @brief OpenGL Index Buffer
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-30
 */
#pragma once
#ifndef GUARD_8295b6ae15ef4ff0bfe31b5dab3f0f16
#define GUARD_8295b6ae15ef4ff0bfe31b5dab3f0f16

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/index_buffer.h"

#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics {

class IndexBuffer::Impl {
    friend class IndexBuffer;
public:
    Impl(NativeHandle device, IndexBuffer &index_buffer, Size size, const void *data);
    ~Impl();

    Impl &operator=(const Impl&) = delete;
private:
    IndexBuffer &index_buffer_;
};
    
} // namespace graphics
} // namespace temp

#endif

#endif // GUARD_8295b6ae15ef4ff0bfe31b5dab3f0f16
