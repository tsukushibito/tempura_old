/**
 * @file device_impl_opengl.h
 * @brief opengl graphics device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-28
 */
#pragma once
#ifndef GUARD_fe71dbd70e5c46bca52dfc7c608632dd
#define GUARD_fe71dbd70e5c46bca52dfc7c608632dd

#include "temp/type.h"
#include "temp/graphics/device.h"

#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics {

class Device::Impl {
    friend class Device;
private:
    Impl(Device &device);
    ~Impl();
	Impl &operator= (const Impl&) = delete;

    VertexShaderSPtr createVertexShaderFromSource(const String &source);
    VertexShaderSPtr createVertexShaderFromBinary(const String &binary);

    PixelShaderSPtr createPixelShaderFromSource(const String &source);
    PixelShaderSPtr createPixelShaderFromBinary(const String &binary);

private:
    Device &device_;
    opengl::OpenglContexts contexts_;
};
    
} // namespace graphics
} // namespace temp
#endif // GUARD_fe71dbd70e5c46bca52dfc7c608632dd
