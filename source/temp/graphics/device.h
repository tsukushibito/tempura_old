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
#include "temp/system/window.h"
#include "temp/type.h"

namespace temp {
namespace graphics {

class Device;
using DeviceHandle = temp::Handle<Device>;

class Device : public SmartPointerObject<Device> {
public:
    static SPtr create(const temp::system::WindowHandle& window_handle);

private:
    explicit Device(const temp::system::WindowHandle& window_handle);

public:
    ~Device();

    DeviceHandle handle();

    TextureSPtr createTexture(const TextureDesc& desc);

    VertexBufferSPtr createVertexBuffer(Size size, void* data);

    IndexBufferSPtr createIndexBuffer(Size size, void* data);

    VertexShaderSPtr createVertexShaderFromSource(Size size, void* sourceCode);
    VertexShaderSPtr createVertexShaderFromBinary(Size size, void* binaryCode);

    PixelShaderSPtr createPixelShaderFromSource(Size size, void* sourceCode);
    PixelShaderSPtr createPixelShaderFromBinary(Size size, void* binaryCode);

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
}
}

#endif  // GUARD_fd7eefec960241e28c2cf1c986bf4ebf
