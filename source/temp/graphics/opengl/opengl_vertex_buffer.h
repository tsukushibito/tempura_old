/**
 * @file opengl_vertex_buffer.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-05-26
 */
#pragma once
#ifndef GUARD_73bbae09484f4d1cbc6f2ed172d0e3e4
#define GUARD_73bbae09484f4d1cbc6f2ed172d0e3e4

#include "temp/graphics/graphics_common.h"
#include "temp/graphics/vertex_buffer.h"

#ifdef TEMP_GRAPHICS_OPENGL
namespace temp {
namespace graphics {
namespace opengl {

class OpenGLVertexBuffer : public VertexBufferBase<OpenGLVertexBuffer, GLuint> {
    friend class SmartPointerObject<OpenGLVertexBuffer>;
    friend Device;

private:
    OpenGLVertexBuffer(GLuint native_handle, const ByteData& data,
                       const std::function<void(GLuint)> on_destroy)
        : VertexBufferBase(native_handle, data, on_destroy) {}
};
}
}
}
#endif

#endif  // GUARD_73bbae09484f4d1cbc6f2ed172d0e3e4
