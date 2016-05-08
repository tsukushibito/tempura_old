/**
 * @file index_buffer.h
 * @brief Index Buffer
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-30
 */
#pragma once
#ifndef GUARD_671315b71a154c4d8df0a7c87e8c02f0
#define GUARD_671315b71a154c4d8df0a7c87e8c02f0

#include "temp/define.h"
#include "temp/type.h"
#include "temp/container.h"

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {

class IndexBuffer : public SmartPointerObject< IndexBuffer >, public FastPImpl {
    friend class Device;

private:
    static SPtr create(NativeHandle device, Size size, const void *data);

    IndexBuffer(NativeHandle device, Size size, const void *data);

public:
    ~IndexBuffer();

    const NativeHandle &getNativeHandle() const { return native_handle_; }

private:
    class Impl;
    Impl *impl_;

    NativeHandle native_handle_;
};
    
} // namespace graphics
} // namespace temp


#endif // GUARD_671315b71a154c4d8df0a7c87e8c02f0
