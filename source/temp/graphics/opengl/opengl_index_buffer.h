/**
 * @file opengl_index_buffer.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-05-26
 */
#pragma once
#ifndef GUARD_2e19dbe90cc14d92a0fd35ad3917ece0
#define GUARD_2e19dbe90cc14d92a0fd35ad3917ece0

#include "temp/graphics/graphics_common.h"
#include "temp/graphics/index_buffer.h"

#ifdef TEMP_GRAPHICS_OPENGL
namespace temp {
namespace graphics {
namespace opengl {

class OpenGLIndexBuffer : public IndexBufferBase<OpenGLIndexBuffer, GLuint> {
    friend class SmartPointerObject<OpenGLIndexBuffer>;
    friend Device;

private:
    OpenGLIndexBuffer(GLuint native_handle, const ByteData& data,
                      const std::function<void(GLuint)> on_destroy)
        : IndexBufferBase(native_handle, data, on_destroy) {}
};
}
}
}
#endif

#endif  // GUARD_2e19dbe90cc14d92a0fd35ad3917ece0
