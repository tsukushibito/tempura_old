/**
 * @file vertex_buffer_impl_opengl.h
 * @brief OpenGL Vertex Buffer
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-30
 */
#pragma once
#ifndef GUARD_c938b64c08364ae28df239e8d910c6b1
#define GUARD_c938b64c08364ae28df239e8d910c6b1

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/vertex_buffer.h"
#include "temp/type.h"

#include "temp/graphics_old/opengl/opengl_common.h"

namespace temp {
namespace graphics_old {

class VertexBuffer::Impl {
    friend class VertexBuffer;

public:
    Impl(NativeHandle device, VertexBuffer& vertex_buffer, Size size,
         const void* data);
    ~Impl();

    Impl& operator=(const Impl&) = delete;

private:
    VertexBuffer& vertex_buffer_;

    // using VertexArrayObjectTable = HashMap<Context::SPtr>;
};

}  // namespace graphics
}  // namespace temp

#endif

#endif  // GUARD_c938b64c08364ae28df239e8d910c6b1
