/**
 * @file input_layout.h
 * @brief input layout
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-05-07
 */
#pragma once
#ifndef GUARD_9202e079ff76410abd7cbe8be9a76a49
#define GUARD_9202e079ff76410abd7cbe8be9a76a49

#include "temp/container.h"
#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics_old/graphics_common.h"

namespace temp {
namespace graphics_old {

class InputLayout : public SmartPointerObject<InputLayout>, public FastPImpl {
    friend class Device;

private:
    static SPtr create(NativeHandle           device,
                       const InputElementDesc element_descs[],
                       UInt32                 element_count);

    InputLayout(NativeHandle device, const InputElementDesc element_descs[],
                UInt32 element_count);

public:
    ~InputLayout();

    const NativeHandle& getNativeHandle() const { return native_handle_; }

private:
    class Impl;
    Impl* impl_;

    NativeHandle native_handle_;
};

}  // namespace graphics
}  // namespace temp

#endif  // GUARD_9202e079ff76410abd7cbe8be9a76a49
