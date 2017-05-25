/**
 * @file vertex_shader.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-05-04
 */
#pragma once
#ifndef GUARD_6bf883f6b4e142a7be00e81e6a33e24e
#define GUARD_6bf883f6b4e142a7be00e81e6a33e24e

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {

template <typename T, typename NativeHandle>
class VertexShaderBase : public SmartPointerObject<T> {
    friend Device;

protected:
    VertexShaderBase(NativeHandle native_handle, const ShaderCode& code,
                     const std::function<void(NativeHandle)> on_destroy)
        : native_handle_(native_handle), code_(code), on_destroy_(on_destroy) {}

public:
    ~VertexShaderBase() { on_destroy_(native_handle_); }

    NativeHandle      nativeHandle() const { return native_handle_; }
    const ShaderCode& code() const { return code_; }

private:
    NativeHandle                      native_handle_;
    ShaderCode                        code_;
    std::function<void(NativeHandle)> on_destroy_;
};
}
}

#endif  // GUARD_6bf883f6b4e142a7be00e81e6a33e24e
