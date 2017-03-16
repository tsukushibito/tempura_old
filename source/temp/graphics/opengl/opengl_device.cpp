/**
 * @file opengl_device.cpp
 * @brief OpenGL device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-14
 */

#include "temp/graphics/opengl/opengl_device.h"
#include "temp/system/window.h"
#ifdef TEMP_PLATFORM_MAC
#include "temp/graphics/opengl/mac/opengl_mac.h"
#endif

namespace temp {
namespace graphics {
namespace opengl {

OpenGlDevice::OpenGlDevice(const temp::system::WindowHandle& window_handle) {
#ifdef TEMP_PLATFORM_MAC
    device_handle_ = mac::createContext(window_handle);
#endif
}
}
}
}
