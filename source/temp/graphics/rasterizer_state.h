/**
 * @file rasterizer_state.h
 * @brief Rasterizer State
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-24
 */
#pragma once
#ifndef GUARD_51943500d29b4b6182efb7e06562824b
#define GUARD_51943500d29b4b6182efb7e06562824b
#include "temp/define.h"
#include "temp/type.h"
#include "temp/container.h"

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {
    
class RasterizerState : public SmartPointerObject<RasterizerState>, public FastPImpl {
    friend class Device;

private:
    static SPtr create(NativeHandle device, const RasterizerDesc &desc);

    RasterizerState(NativeHandle device, const RasterizerDesc &desc);

public:
    ~RasterizerState();

    const NativeHandle &getNativeHandle() const { return native_handle_; }

private:
    class Impl;
    Impl *impl_;

    NativeHandle native_handle_;
};

} // namespace graphics
} // namespace temp

#endif // GUARD_51943500d29b4b6182efb7e06562824b
