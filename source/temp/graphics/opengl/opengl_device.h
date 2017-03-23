/**
 * @file opengl_device.h
 * @brief OpenGLデバイス
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-02-28
 */
#pragma once
#ifndef GUARD_c63f349cadc54355a8cca8adfd97d484
#define GUARD_c63f349cadc54355a8cca8adfd97d484

#include "temp/type.h"

#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/system/thread_pool.h"

#include "temp/graphics/device.h"
#include "temp/graphics/opengl/opengl_define.h"

namespace temp {
namespace graphics {
namespace opengl {

#if defined(TEMP_PLATFORM_MAC)
using NativeHandle = void*;
using NativeWindowHandle = void*;
#elif defined(TEMP_PLATFORM_WINDOWS)
using NativeHandle = HGLRC;
using NativeWindowHandle = HWND;
#endif

class OpenGLDevice : public DeviceBase<OpenGLDevice, NativeHandle>,
                     public SmartPointerObject<OpenGLDevice> {
    friend class SmartPointerObject<OpenGLDevice>;

private:
    explicit OpenGLDevice(NativeWindowHandle window_handle);

public:
    NativeHandle nativeHandle() const { return context_; }

private:
    NativeHandle context_;
	temp::system::ThreadPool::UPtr resource_creation_thread_;
};
}
}
}

#endif  // TEMP_GRAPHICS_OPENGL

#endif  // GUARD_c63f349cadc54355a8cca8adfd97d484
