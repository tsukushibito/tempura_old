/**
 * @file pixel_shader.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-05-04
 */
#pragma once
#ifndef GUARD_30805b62ea474d99b57fa42fab463beb
#define GUARD_30805b62ea474d99b57fa42fab463beb

#include "temp/container.h"

#include "temp/graphics_/graphics_common.h"

namespace temp {
namespace graphics_ {

template <typename T, typename NativeHandle>
class PixelShaderBase : public SmartPointerObject<T> {
    friend Device;

protected:
    PixelShaderBase(NativeHandle native_handle, const ShaderCode& code,
                    const std::function<void(NativeHandle)> on_destroy)
        : native_handle_(native_handle), code_(code), on_destroy_(on_destroy) {}

public:
    ~PixelShaderBase() { on_destroy_(native_handle_); }

    NativeHandle      nativeHandle() const { return native_handle_; }
    const ShaderCode& code() const { return code_; }

private:
    NativeHandle                      native_handle_;
    ShaderCode                        code_;
    std::function<void(NativeHandle)> on_destroy_;
};
}
}

#endif  // GUARD_30805b62ea474d99b57fa42fab463beb
