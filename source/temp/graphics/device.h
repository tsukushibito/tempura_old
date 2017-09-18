/**
 * @file device.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-02-27
 */
#pragma once
#ifndef GUARD_fd7eefec960241e28c2cf1c986bf4ebf
#define GUARD_fd7eefec960241e28c2cf1c986bf4ebf

#include <memory>
#include <mutex>
#include <vector>

#include "temp/graphics/graphics_common.h"

#include "temp/system/window.h"

#include "temp/graphics/index_buffer.h"
#include "temp/graphics/pixel_shader.h"
#include "temp/graphics/render_target.h"
#include "temp/graphics/texture.h"
#include "temp/graphics/vertex_buffer.h"
#include "temp/graphics/vertex_shader.h"

namespace temp {
namespace graphics {

template <typename T, typename NativeHandle>
class DeviceBase : public SmartPointerObject<T> {
public:
    NativeHandle nativeHandle() const { return native_handle_; }

    RenderTargetSPtr createRenderTarget(const RenderTargetDesc& desc) {
        return derived()->createRenderTarget(desc);
    }

    TextureSPtr createTexture(const TextureDesc& desc, const void* data) {
        return derived()->createTexture(desc);
    }

    VertexBufferSPtr createVertexBuffer(const VertexBufferDesc& desc,
                                        const void*             data) {
        return derived()->createVertexBuffer(desc, data);
    }

    IndexBufferSPtr createIndexBuffer(const IndexBufferDesc& desc,
                                      const void*            data) {
        return derived()->createIndexBuffer(desc, data);
    }

    PixelShaderSPtr createPixelShader(const ShaderCode& code) {
        return derived()->createPixelShader(code);
    }

    VertexShaderSPtr createVertexShader(const ShaderCode& code) {
        return derived()->createVertexShader(code);
    }

    NativeHandle nativeHandle() { return native_handle_; }

    NativeWindowHandle nativeWindowHandle() { return native_window_handle_; }


private:
    T* derived() const { return static_cast<T*>(this); }

protected:
    NativeHandle native_handle_;
    NativeWindowHandle native_window_handle_;
};
}
}

#endif  // GUARD_fd7eefec960241e28c2cf1c986bf4ebf
