/**
 * @file opengl_device.cpp
 * @brief OpenGL device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-14
 */

#include "temp/graphics/opengl/opengl_device.h"
#include "temp/system/window.h"
#if defined(TEMP_PLATFORM_MAC)
#include "temp/graphics/opengl/mac/opengl_mac.h"
#elif defined(TEMP_PLATFORM_WINDOWS)
#include "temp/graphics/opengl/windows/opengl_windows.h"
#endif

namespace temp {
namespace graphics {
namespace opengl {

DeviceHandle createContext(const temp::system::WindowHandle& window_handle) {
#if defined(TEMP_PLATFORM_MAC)
    return mac::createContext(window_handle);
#elif defined(TEMP_PLATFORM_WINDOWS)
    return windows::createContext(window_handle);
#endif
}

OpenGlDevice::OpenGlDevice(const temp::system::WindowHandle& window_handle) {
    device_handle_ = createContext(window_handle);
}
}
}
}
