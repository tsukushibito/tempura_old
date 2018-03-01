/**
 * @file device_impl_opengl.h
 * @brief opengl graphics device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-28
 */
#pragma once
#ifndef GUARD_fe71dbd70e5c46bca52dfc7c608632dd
#define GUARD_fe71dbd70e5c46bca52dfc7c608632dd

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/device.h"
#include "temp/type.h"

#include "temp/graphics_old/opengl/opengl_common.h"

namespace temp {
namespace graphics_old {

class Device::Impl {
    friend class Device;

private:
    Impl(Device& device);
    ~Impl();
    Impl& operator=(const Impl&) = delete;

    ContextSPtr createContext();

    void executeCommands(const ContextSPtr& context);
    void present();  // 仮
private:
    Device&                device_;
    opengl::OpenglContexts contexts_;
};

}  // namespace graphics
}  // namespace temp
#endif  // TEMP_GRAPHICS_OPENGL
#endif  // GUARD_fe71dbd70e5c46bca52dfc7c608632dd
