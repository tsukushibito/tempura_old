/**
 * @file vertex_buffer.h
 * @brief vertex buffer
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-03
 */
#pragma once
#ifndef GUARD_ac1d8ba60f374031a8954034301ca4b8
#define GUARD_ac1d8ba60f374031a8954034301ca4b8

#include "temp/container.h"
#include "temp/define.h"
#include "temp/type.h"
#include "temp/utility.h"

#include "temp/graphics_old/graphics_common.h"

namespace temp {
namespace graphics_old {

class VertexBuffer : public SmartPointerObject<VertexBuffer>, public FastPImpl {
    friend class Device;

private:
    static SPtr create(NativeHandle device, Size size, const void* data);

    VertexBuffer(NativeHandle device, Size size, const void* data);

public:
    ~VertexBuffer();

    const NativeHandle& getNativeHandle() const { return native_handle_; }

    void addOnDeleteEvent(const std::function<void()>& func) {
        on_delete_event_.addFunction(func);
    }

private:
    class Impl;
    Impl* impl_;

    NativeHandle native_handle_;

    Event on_delete_event_;
};

}  // namespace graphics
}  // namespace temp

#endif  // GUARD_ac1d8ba60f374031a8954034301ca4b8
