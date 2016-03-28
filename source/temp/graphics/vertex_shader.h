/**
 * @file vertex_shader.h
 * @brief vertex shader
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-03
 */
#pragma once
#ifndef GUARD_f1056eab392c46308d7e8e0e3fa3aa79
#define GUARD_f1056eab392c46308d7e8e0e3fa3aa79

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {

class VertexShader : public SmartPointerObject<VertexShader> , public FastPImpl {
    friend class Device;
private:
    VertexShader(const NativeHandle &native_handle);

public:
    ~VertexShader();

    const NativeHandle &getNativeHandle() const { return native_handle_; }

private:
    class Impl;
    Impl *impl_;

    NativeHandle native_handle_;
};
    
} // namespace graphics
} // namespace temp

#endif // GUARD_f1056eab392c46308d7e8e0e3fa3aa79
