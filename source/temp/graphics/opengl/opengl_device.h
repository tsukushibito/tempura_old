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

#include "temp/graphics/opengl/opengl_define.h"
#include "temp/type.h"

#ifdef TEMP_GRAPHICS_OPENGL

#include "temp/graphics/device.h"
namespace temp {
namespace system {
class Window;
using WindowHandle = Handle<Window>;
}
}

namespace temp {
namespace graphics {
namespace opengl {

class OpenGlDevice {
public:
    explicit OpenGlDevice(const temp::system::WindowHandle& window_handle);

    const DeviceHandle& handle() const { return device_handle_; }

private:
    DeviceHandle device_handle_;
};
}
}
}

#endif  // TEMP_GRAPHICS_OPENGL

#endif  // GUARD_c63f349cadc54355a8cca8adfd97d484
