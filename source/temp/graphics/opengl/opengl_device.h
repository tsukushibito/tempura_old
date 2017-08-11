/**
 * @file opengl_device.h
 * @brief OpenGLデバイス
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-02-28
 */
#pragma once
#ifndef GUARD_c63f349cadc54355a8cca8adfd97d484
#define GUARD_c63f349cadc54355a8cca8adfd97d484

#include "temp/graphics/graphics_common.h"

#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/system/thread_pool.h"

#include "temp/graphics/device.h"
#include "temp/graphics/opengl/opengl_define.h"

namespace temp {
namespace graphics {
namespace opengl {

class OpenGLDevice : public DeviceBase<OpenGLDevice, OpenGLContextHandle> {
    friend class SmartPointerObject<OpenGLDevice>;

private:
    explicit OpenGLDevice(NativeWindowHandle window_handle);

public:
    TextureSPtr createTexture(const TextureDesc& desc);

    VertexBufferSPtr createVertexBuffer(const VertexBufferDesc& desc,
                                        const void*             data);

    IndexBufferSPtr createIndexBuffer(const IndexBufferDesc& desc,
                                      const void*            data);

    PixelShaderSPtr createPixelShader(const ShaderCode& code);

    VertexShaderSPtr createVertexShader(const ShaderCode& code);

private:
    template <typename TaskType>
    auto execInResourceCreationThread(TaskType& task) -> decltype(task());

    temp::system::ThreadPool::SPtr resource_creation_thread_;
};
}
}
}

#endif  // TEMP_GRAPHICS_OPENGL

#endif  // GUARD_c63f349cadc54355a8cca8adfd97d484
