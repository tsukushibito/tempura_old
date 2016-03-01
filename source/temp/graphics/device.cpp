/**
 * @file device.cpp
 * @brief graphics device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-29
 */
#include <new>

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics/device.h"
#if defined TEMP_GRAPHICS_D3D11
#include "temp/graphics/d3d11/device_d3d11.h"
#elif defined TEMP_GRAPHICS_OPENGL
#include "temp/graphics/opengl/device_opengl.h"
#endif

namespace temp {
namespace graphics {

void Device::initialize() {
}

void Device::terminate() {
}

Device::SPtr Device::create() {
    struct Creator : public Device {
    };

    auto ptr = std::make_shared<Creator>();
    return std::move(ptr);
}

Device::Device() {

}
    
} // namespace graphics
} // namespace temp

