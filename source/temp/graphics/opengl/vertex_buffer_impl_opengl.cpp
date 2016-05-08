/**
 * @file vertex_buffer_impl_opengl.cpp
 * @brief OpenGL Vertex Buffer
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-30
 */

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/vertex_buffer.h"

#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/vertex_buffer_impl_opengl.h"

namespace temp {
namespace graphics {

VertexBuffer::Impl::Impl(NativeHandle device, VertexBuffer &vertex_buffer, Size size, const void *data)
    : vertex_buffer_(vertex_buffer) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    vertex_buffer_.native_handle_.value_ = vbo;

    temp::system::ConsoleLogger::trace("OpenGL Vertex Buffer has created! id = {0}", vertex_buffer_.native_handle_.value_);
        
    (void)device;
}

VertexBuffer::Impl::~Impl() {
    using namespace opengl;

    glDeleteBuffers(1, (GLuint*)&vertex_buffer_.native_handle_.value_);

    temp::system::ConsoleLogger::trace("OpenGL Vertex Buffer has deleted! id = {0}", vertex_buffer_.native_handle_.value_);
}

    
} // namespace graphics
} // namespace temp
#endif
