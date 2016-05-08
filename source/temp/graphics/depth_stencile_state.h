/**
 * @file depth_stencile_state.h
 * @brief Depth Stencile State
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-23
 */
#pragma once
#ifndef GUARD_7b20e55c7a7749c7b4afae18796ffad2
#define GUARD_7b20e55c7a7749c7b4afae18796ffad2
#include "temp/define.h"
#include "temp/type.h"
#include "temp/container.h"

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace graphics {
    
class DepthStencileState : public SmartPointerObject<DepthStencileState>, public FastPImpl {
    friend class Device;

private:
    static SPtr create(NativeHandle device, DepthStencileFunc depth_func, DepthStencileFunc stencile_func);

    DepthStencileState(NativeHandle device, DepthStencileFunc depth_func, DepthStencileFunc stencile_func);

public:
    ~DepthStencileState();

    const NativeHandle &getNativeHandle() const { return native_handle_; }

private:
    class Impl;
    Impl *impl_;

    NativeHandle native_handle_;
};

} // namespace graphics
} // namespace temp

#endif // GUARD_7b20e55c7a7749c7b4afae18796ffad2
