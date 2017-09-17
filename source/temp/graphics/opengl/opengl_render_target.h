/**
 * @file opengl_render_target.h
 * @brief 
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-08-23
 */
#pragma once
#ifndef GUARD_afd7a77bd6c94616b49d719c0d7a0d40
#define GUARD_afd7a77bd6c94616b49d719c0d7a0d40

#include "temp/system/thread_pool.h"

#include "temp/graphics/graphics_common.h"
#include "temp/graphics/render_target.h"

#ifdef TEMP_GRAPHICS_OPENGL
namespace temp {
namespace graphics {
namespace opengl {

class OpenGLRenderTarget : public RenderTargetBase<OpenGLRenderTarget, GLuint> {
    friend class SmartPointerObject<OpenGLRenderTarget>;
    friend Device;

private:
    OpenGLRenderTarget(GLuint native_handle, const RenderTargetDesc& desc,
                  const std::function<void(GLuint)>     on_destroy,
                  const temp::system::ThreadPool::SPtr& device_thread)
        : RenderTargetBase(native_handle, desc, on_destroy)
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
#endif // GUARD_afd7a77bd6c94616b49d719c0d7a0d40
