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

#include "temp/system/thread_pool.h"

#include "temp/graphics_/graphics_common.h"
#include "temp/graphics_/index_buffer.h"

#ifdef TEMP_GRAPHICS_OPENGL
namespace temp {
namespace graphics_ {
namespace opengl {

class OpenGLIndexBuffer : public IndexBufferBase<OpenGLIndexBuffer, GLuint> {
    friend class SmartPointerObject<OpenGLIndexBuffer>;
    friend Device;

private:
    OpenGLIndexBuffer(GLuint native_handle, const IndexBufferDesc& desc,
                      const std::function<void(GLuint)>     on_destroy,
                      const temp::system::ThreadPool::SPtr& device_thread)
        : IndexBufferBase(native_handle, desc, on_destroy)
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

#endif  // GUARD_2e19dbe90cc14d92a0fd35ad3917ece0
