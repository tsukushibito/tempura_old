/**
 * @file blend_state.h
 * @brief blend state
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-18
 */
#pragma once
#ifndef GUARD_79e9e2f3f8f849b79f4f5d26f50f965f
#define GUARD_79e9e2f3f8f849b79f4f5d26f50f965f
#include "temp/define.h"
#include "temp/type.h"
#include "temp/container.h"

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {

class BlendState : public SmartPointerObject< BlendState >, public FastPImpl {
    friend class Device;

private:
    static SPtr create(NativeHandle device);

    BlendState(NativeHandle device);

public:
    ~BlendState();

    const NativeHandle &getNativeHandle() const { return native_handle_; }

private:
    class Impl;
    Impl *impl_;

    NativeHandle native_handle_;
};

}
}

#endif // GUARD_79e9e2f3f8f849b79f4f5d26f50f965f
