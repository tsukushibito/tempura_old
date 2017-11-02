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

#include "temp/system/thread_pool.h"

#include "temp/graphics_/graphics_common.h"
#include "temp/graphics_/vertex_buffer.h"

#ifdef TEMP_GRAPHICS_OPENGL
namespace temp {
namespace graphics_ {
namespace opengl {

class OpenGLVertexBuffer : public VertexBufferBase<OpenGLVertexBuffer, GLuint> {
    friend class SmartPointerObject<OpenGLVertexBuffer>;
    friend Device;

private:
    OpenGLVertexBuffer(GLuint native_handle, const VertexBufferDesc& desc,
                       const std::function<void(GLuint)>     on_destroy,
                       const temp::system::ThreadPool::SPtr& device_thread)
        : VertexBufferBase(native_handle, desc, on_destroy)
        , device_thread_(device_thread) {}

public:
    const ByteData data() const;

private:
    temp::system::ThreadPool::SPtr device_thread_;
};
}
}
}
#endif

#endif  // GUARD_73bbae09484f4d1cbc6f2ed172d0e3e4
