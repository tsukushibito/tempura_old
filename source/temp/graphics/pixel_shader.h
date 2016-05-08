/**
 * @file pixel_shader.h
 * @brief pixel shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-29
 */
#pragma once
#ifndef GUARD_b23655b3e56e47879ef703e057f92ed8
#define GUARD_b23655b3e56e47879ef703e057f92ed8

#include "temp/define.h"
#include "temp/type.h"
#include "temp/container.h"

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {

class PixelShader : public SmartPointerObject<PixelShader> , public FastPImpl {
    friend class Device;
private:
    static SPtr create(NativeHandle device, const String &source, Bool is_binary);

    PixelShader(NativeHandle device, const String &source, Bool is_binary);

public:
    ~PixelShader();

    const NativeHandle &getNativeHandle() const { return native_handle_; }

private:
    class Impl;
    Impl *impl_;

    NativeHandle native_handle_;
};
    
} // namespace graphics
} // namespace temp

#endif // GUARD_b23655b3e56e47879ef703e057f92ed8
