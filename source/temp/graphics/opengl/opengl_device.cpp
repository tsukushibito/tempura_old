/**
 * @file opengl_device.cpp
 * @brief OpenGL device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-14
 */

#include "temp/define.h"

#include "temp/graphics/opengl/opengl_device.h"
#if defined(TEMP_PLATFORM_MAC)
#include "temp/graphics/opengl/mac/opengl_mac.h"
#elif defined(TEMP_PLATFORM_WINDOWS)
#include "temp/graphics/opengl/windows/opengl_windows.h"
#endif

#include "temp/system/window.h"

namespace temp {
namespace graphics {
namespace opengl {

OpenGLDevice::OpenGLDevice(const temp::system::WindowHandle& window_handle) {
    context_ = mac::createContext(window_handle);
}
}
}
}
