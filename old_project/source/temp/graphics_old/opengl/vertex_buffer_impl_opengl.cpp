/**
 * @file vertex_buffer_impl_opengl.cpp
 * @brief OpenGL Vertex Buffer
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-30
 */

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/vertex_buffer.h"
#include "temp/type.h"

#include "temp/graphics_old/opengl/opengl_common.h"
#include "temp/graphics_old/opengl/vertex_buffer_impl_opengl.h"

namespace temp {
namespace graphics_old {

VertexBuffer::Impl::Impl(NativeHandle device, VertexBuffer& vertex_buffer,
                         Size size, const void* data)
    : vertex_buffer_(vertex_buffer) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    vertex_buffer_.native_handle_.value = vbo;

    temp::system::Logger::trace(
        "OpenGL Vertex Buffer has created! id = {0}",
        vertex_buffer_.native_handle_.value);

    (void)device;
}

VertexBuffer::Impl::~Impl() {
    using namespace opengl;

    glDeleteBuffers(1, (GLuint*)&vertex_buffer_.native_handle_.value);

    temp::system::Logger::trace(
        "OpenGL Vertex Buffer has deleted! id = {0}",
        vertex_buffer_.native_handle_.value);
}


}  // namespace graphics
}  // namespace temp
#endif
