/**
 * @file opengl_texture.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-05-05
 */
#pragma once
#ifndef GUARD_d6e18923b7fc46689be98b8d23800676
#define GUARD_d6e18923b7fc46689be98b8d23800676

#include "temp/system/thread_pool.h"

#include "temp/graphics_/graphics_common.h"
#include "temp/graphics_/texture.h"

#ifdef TEMP_GRAPHICS_OPENGL
namespace temp {
namespace graphics_ {
namespace opengl {

class OpenGLTexture : public TextureBase<OpenGLTexture, GLuint> {
    friend class SmartPointerObject<OpenGLTexture>;
    friend Device;

private:
    OpenGLTexture(GLuint native_handle, const TextureDesc& desc,
                  const std::function<void(GLuint)>     on_destroy,
                  const temp::system::ThreadPool::SPtr& device_thread)
        : TextureBase(native_handle, desc, on_destroy)
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

#endif  // GUARD_d6e18923b7fc46689be98b8d23800676
