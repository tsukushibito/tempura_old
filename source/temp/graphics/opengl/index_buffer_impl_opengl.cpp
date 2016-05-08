/**
 * @file index_buffer_impl_opengl.cpp
 * @brief OpenGL Index Buffer
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-30
 */

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/vertex_buffer.h"

#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/index_buffer_impl_opengl.h"

namespace temp {
namespace graphics {

IndexBuffer::Impl::Impl(NativeHandle device, IndexBuffer &index_buffer, Size size, const void *data)
    : index_buffer_(index_buffer) {
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    index_buffer_.native_handle_.value_ = ibo;

    temp::system::ConsoleLogger::trace("OpenGL Index Buffer has created! id = {0}", index_buffer_.native_handle_.value_);
        
    (void)device;
}

IndexBuffer::Impl::~Impl() {
    using namespace opengl;

    glDeleteBuffers(1, (GLuint*)&index_buffer_.native_handle_.value_);

    temp::system::ConsoleLogger::trace("OpenGL Index Buffer has deleted! id = {0}", index_buffer_.native_handle_.value_);
}

    
} // namespace graphics
} // namespace temp
#endif
