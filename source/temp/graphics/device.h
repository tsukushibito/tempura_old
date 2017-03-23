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
#include "temp/system/window.h"
#include "temp/type.h"

namespace temp {
namespace graphics {

template <typename T, typename NativeHandle>
class DeviceBase {
public:
    NativeHandle nativeHandle() const { return derived()->nativeHandle(); }

	// TextureSPtr createTexture(const TextureDesc& desc) { return derived()->createTexture(desc); }

    // VertexBufferSPtr createVertexBuffer(Size size, void* data);

    // IndexBufferSPtr createIndexBuffer(Size size, void* data);

    // VertexShaderSPtr createVertexShaderFromSource(Size size, void*
    // sourceCode);
    // VertexShaderSPtr createVertexShaderFromBinary(Size size, void*
    // binaryCode);

    // PixelShaderSPtr createPixelShaderFromSource(Size size, void* sourceCode);
    // PixelShaderSPtr createPixelShaderFromBinary(Size size, void* binaryCode);

private:
    T* derived() const { return static_cast<T*>(this); }
};
}
}

#endif  // GUARD_fd7eefec960241e28c2cf1c986bf4ebf
